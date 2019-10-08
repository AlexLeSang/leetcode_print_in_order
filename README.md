## Solutions for leetcode [Print in Order](https://leetcode.com/problems/print-in-order/ )

Solution based on condition_variable

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `build/print-in-order-condition-variables` | 408.8 ± 4.2 | 400.4 | 414.7 | 1.0 |

Solution with atomic integer.

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `build/print-in-order-atomic` | 403.2 ± 9.8 | 389.0 | 422.5 | 1.0 |

Solution with two atomic booleans.

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `build/print-in-order-two-atomic-bools` | 405.4 ± 9.3 | 391.7 | 421.9 | 1.0 |
