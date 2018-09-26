#include <stdio.h>
#include <time.h>

int main()
{
	double limit;
	int n = 0;
	double items[64];

    FILE *file = fopen("input", "r");
    fscanf(file, "%lf", &limit);
    while (fscanf(file, "%lf", &items[n]) > 0)
        n++;
    fclose(file);
    struct timespec time_start;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    double sum_best = 0;
    long mask_best = 0x0;
    for (long mask = 0; mask < 0x1<<(n-1); mask++) {
    	double sum = 0;
    	for (int i = 0; i < n; i++)
    		if ((mask >> i) & 0x1)
    			sum += items[i];
    	if (sum_best < sum && sum <= limit) {
    		sum_best = sum;
    		mask_best = mask;
    	}
    }

	struct timespec time_end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_end);
    double time = 1e-9 * (time_end.tv_nsec - time_start.tv_nsec) + (time_end.tv_sec - time_start.tv_sec);
    printf("time: %.3f s\n", time);
    printf("elements: %d / %d\n", __builtin_popcountl(mask_best), n);
    printf("sum: %.9f / %g\n", sum_best, limit);
    while (n--) {
        if (mask_best & 0x1)
            printf("%.9f  ", items[n]);
        mask_best >>= 1;
    }
    puts("");
    return 0;
}