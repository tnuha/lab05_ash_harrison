# Results

## Activity 1: Timekeeping

| Program | Busy-wait | Mean | Std dev | Min | Max |
|---|---|---|---|---|---|
| task_delay | 0 | 20 ms | 458.47 ns | 19.999 ms | 20.000 ms |
| timer | 0 | 20 ms | 475 ns | 19.999 ms | 20.000 ms |
| sleep | 0 | 20 ms | 468 ns | 19.999 ms | 20.000 ms |
| task_delay | 10000 | 20 ms | 474.82 ns | 19.998 ms | 20.001 ms |
| timer | 10000 | 20 ms | 470.17 ns | 19.999 ms | 20.000 ms |
| sleep | 10000 | 21.6 ms | 484.53 ns | 21.599 ms | 21.600 ms |
| task_delay | 20000 | 22 ms | 490.63 ns | 21.999 ms | 22.000 ms |
| Wave Gen | - | 19.999 ms | 0 | 19.999 ms | 19.999 ms |

## Activity 2: Interrupt Latency

| Busy-wait | Latency |
|---|---|
| 0 | 1.63 us |
| 100 | 9.66 us |
| 1000 | 81.6 us |
| 10000 | 802 us |

## Activity 3: Scheduler

| Busy tasks | Mean | Std dev | Min | Max |
|---|---|---|---|---|
| 1 | 1.999 ms | 784.5 ns | 1.9976 ms | 2.0024 ms |
| 2 | 3.9998 ms | 851.35 ns | 3.9976 ms | 4.0021 ms |
