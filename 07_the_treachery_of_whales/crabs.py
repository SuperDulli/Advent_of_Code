
file = open("input", "r")
crabs = file.read().split(",")
crabs = list(map(int, crabs))

def fuel_cost(positions, target):
    cost = 0
    for p in positions:
        cost += abs(p - target)
    return cost


costs = [fuel_cost(crabs, x) for x in crabs]
print(min(costs))


def expensive_fuel_cost(positions, target):
    cost = 0
    for p in positions:
        cost += sum_all(abs(p - target))
    return cost


def sum_all(n):
    r = 0
    for i in range(0, n + 1):
        r += i
    return r


expensive_costs = [expensive_fuel_cost(crabs, x) for x in range(min(crabs), max(crabs))]
print(min(expensive_costs))
