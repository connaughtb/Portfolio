/*
 * Partitioned real-time task allocator.
 *
 * Reads a set of periodic tasks, assigns them to CPUs using first-fit,
 * best-fit, or worst-fit decreasing, then verifies each CPU partition using
 * utilization checks and fixed-priority response-time analysis.
 */

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 10000U
#define MAX_CPUS 100U
#define NAME_LENGTH 32U
#define UTILIZATION_EPSILON 1e-12

typedef struct {
    char name[NAME_LENGTH];
    uint32_t execution_time;
    uint32_t period;
    double utilization;
} PeriodicTask;

typedef struct {
    double utilization;
    size_t task_count;
    size_t task_indices[MAX_TASKS];
} CpuPartition;

typedef enum { FIRST_FIT, BEST_FIT, WORST_FIT } AllocationPolicy;

static void trim(char *text) {
    size_t length = strlen(text);
    while (length > 0 && isspace((unsigned char)text[length - 1])) {
        text[--length] = '\0';
    }

    size_t first = 0;
    while (text[first] && isspace((unsigned char)text[first])) ++first;
    if (first != 0) memmove(text, text + first, strlen(text + first) + 1);
}

static int compare_descending_utilization(const void *left, const void *right) {
    const PeriodicTask *a = left;
    const PeriodicTask *b = right;
    return (a->utilization < b->utilization) - (a->utilization > b->utilization);
}

static int compare_ascending_period(const void *left, const void *right) {
    const PeriodicTask *a = left;
    const PeriodicTask *b = right;
    return (a->period > b->period) - (a->period < b->period);
}

static int parse_policy(const char *text, AllocationPolicy *policy) {
    if (strcmp(text, "FFD") == 0) *policy = FIRST_FIT;
    else if (strcmp(text, "BFD") == 0) *policy = BEST_FIT;
    else if (strcmp(text, "WFD") == 0) *policy = WORST_FIT;
    else return 0;
    return 1;
}

static int periods_are_harmonic(const PeriodicTask *tasks, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            const uint32_t shorter = tasks[i].period < tasks[j].period ? tasks[i].period : tasks[j].period;
            const uint32_t longer = tasks[i].period > tasks[j].period ? tasks[i].period : tasks[j].period;
            if (longer % shorter != 0U) return 0;
        }
    }
    return 1;
}

static int response_time_schedulable(PeriodicTask *tasks, size_t count) {
    qsort(tasks, count, sizeof(*tasks), compare_ascending_period);

    for (size_t i = 0; i < count; ++i) {
        uint64_t previous_response = UINT64_MAX;
        uint64_t response = tasks[i].execution_time;

        while (response != previous_response) {
            previous_response = response;
            uint64_t interference = 0;

            for (size_t j = 0; j < i; ++j) {
                const uint64_t releases = (previous_response + tasks[j].period - 1U) / tasks[j].period;
                interference += releases * tasks[j].execution_time;
            }

            response = tasks[i].execution_time + interference;
            if (response > tasks[i].period) return 0;
        }
    }
    return 1;
}

static int partition_schedulable(const CpuPartition *partition, const PeriodicTask *all_tasks) {
    if (partition->utilization > 1.0 + UTILIZATION_EPSILON) return 0;
    if (partition->task_count == 0) return 1;

    PeriodicTask local_tasks[MAX_TASKS];
    for (size_t i = 0; i < partition->task_count; ++i) {
        local_tasks[i] = all_tasks[partition->task_indices[i]];
    }

    return periods_are_harmonic(local_tasks, partition->task_count) ||
           response_time_schedulable(local_tasks, partition->task_count);
}

static int select_cpu(const CpuPartition *partitions, size_t cpu_count,
                      double task_utilization, AllocationPolicy policy) {
    int selected = -1;
    double selected_remaining = policy == BEST_FIT ? 2.0 : -1.0;

    for (size_t cpu = 0; cpu < cpu_count; ++cpu) {
        const double remaining = 1.0 - (partitions[cpu].utilization + task_utilization);
        if (remaining < -UTILIZATION_EPSILON) continue;

        if (policy == FIRST_FIT) return (int)cpu;
        if (policy == BEST_FIT && remaining < selected_remaining) {
            selected = (int)cpu;
            selected_remaining = remaining;
        }
        if (policy == WORST_FIT && remaining > selected_remaining) {
            selected = (int)cpu;
            selected_remaining = remaining;
        }
    }
    return selected;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <task-set-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Unable to open task-set file");
        return EXIT_FAILURE;
    }

    size_t cpu_count, task_count;
    char policy_text[8];
    if (fscanf(input, " %zu , %7s", &cpu_count, policy_text) != 2 ||
        fscanf(input, " %zu", &task_count) != 1 ||
        cpu_count == 0 || cpu_count > MAX_CPUS || task_count > MAX_TASKS) {
        fprintf(stderr, "Invalid task-set header\n");
        fclose(input);
        return EXIT_FAILURE;
    }
    trim(policy_text);

    AllocationPolicy policy;
    if (!parse_policy(policy_text, &policy)) {
        fprintf(stderr, "Policy must be FFD, BFD, or WFD\n");
        fclose(input);
        return EXIT_FAILURE;
    }

    PeriodicTask tasks[MAX_TASKS];
    for (size_t i = 0; i < task_count; ++i) {
        if (fscanf(input, " %31[^,] , %u , %u", tasks[i].name,
                   &tasks[i].execution_time, &tasks[i].period) != 3 ||
            tasks[i].execution_time == 0U || tasks[i].period == 0U) {
            fprintf(stderr, "Invalid task at index %zu\n", i);
            fclose(input);
            return EXIT_FAILURE;
        }
        trim(tasks[i].name);
        tasks[i].utilization = (double)tasks[i].execution_time / tasks[i].period;
    }
    fclose(input);

    qsort(tasks, task_count, sizeof(*tasks), compare_descending_utilization);

    /* Keep the maximum-size partition table out of the process stack. */
    static CpuPartition partitions[MAX_CPUS];
    memset(partitions, 0, sizeof(partitions));
    for (size_t task = 0; task < task_count; ++task) {
        const int cpu = select_cpu(partitions, cpu_count, tasks[task].utilization, policy);
        if (cpu < 0) {
            puts("Unschedulable: no CPU partition has sufficient capacity.");
            return EXIT_FAILURE;
        }
        CpuPartition *partition = &partitions[cpu];
        partition->utilization += tasks[task].utilization;
        partition->task_indices[partition->task_count++] = task;
    }

    for (size_t cpu = 0; cpu < cpu_count; ++cpu) {
        if (!partition_schedulable(&partitions[cpu], tasks)) {
            printf("Unschedulable: response-time analysis failed on CPU %zu.\n", cpu);
            return EXIT_FAILURE;
        }
    }

    printf("Schedulable task set using %s:\n", policy_text);
    for (size_t cpu = 0; cpu < cpu_count; ++cpu) {
        printf("CPU %zu (U=%.3f):", cpu, partitions[cpu].utilization);
        for (size_t i = 0; i < partitions[cpu].task_count; ++i) {
            printf(" %s", tasks[partitions[cpu].task_indices[i]].name);
        }
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
