import numpy as np
import os

# 2 4 8 16 32
# 10 100 1000 10000 100000


def create_knapsack_instance():
    for n in [8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40]:
        for w in [8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32]:
            if not os.path.exists(f'../data/knapsack-{n}'):
                os.mkdir(f'../data/knapsack-{n}')

            values = np.random.uniform(1, 1000, n)
            weight = np.random.uniform(1, w, n)
            
            with open(f'../data/knapsack-{n}/{w}.txt', 'w') as fp:
                fp.write(f'{n} {w}\n')
                for i in range(n):
                    fp.write(f'{int(weight[i])} {int(values[i])}\n')

if __name__ == "__main__":
    create_knapsack_instance()