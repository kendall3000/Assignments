import numpy as np
import matplotlib.pyplot as plt
import os

def is_ccw(p1, p2, p3):
    return (p2[0] - p1[0]) * (p3[1] - p1[1]) - (p3[0] - p1[0]) * (p2[1] - p1[1])

def compute_convex_hull(points):
    def divide_conquer(points):
        if len(points) <= 3:
            return points

        mid = len(points) // 2
        left_hull = divide_conquer(points[:mid])
        right_hull = divide_conquer(points[mid:])
        return merge_hulls(left_hull, right_hull)

    def merge_hulls(left_hull, right_hull):
        def get_tangent(hull, point, is_clockwise):
            tangent_index = 0
            for i in range(len(hull)):
                if is_ccw(point, hull[i], hull[tangent_index]) == is_clockwise:
                    tangent_index = i
            return tangent_index

        left_tangent_index = get_tangent(left_hull, right_hull[0], True)
        right_tangent_index = get_tangent(right_hull, left_hull[-1], False)

        upper_hull = left_hull[:left_tangent_index+1] + right_hull[right_tangent_index:]
        lower_hull = right_hull[:right_tangent_index+1] + left_hull[left_tangent_index:]

        return upper_hull + lower_hull

    sorted_points = sorted(points, key=lambda p: p[0])
    convex_hull = divide_conquer(sorted_points)
    indices = [points.index(p) for p in convex_hull]
    return indices

def read_points_from_file(filename):
    points = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(float, line.strip().split(','))
            points.append((x, y))
    return points

def write_indices_to_file(filename, indices):
    with open(filename, 'w') as file:
        for index in indices:
            file.write(str(index) + '\n')

input_file = 'input.csv'
output_file = 'output.txt'

if not os.path.exists(input_file):
    print('Cannnot find ' + input_file + '.')
    exit()

points = read_points_from_file(input_file)
convex_hull_indices = compute_convex_hull(points)
write_indices_to_file(output_file, convex_hull_indices)

x = [point[0] for point in points]
y = [point[1] for point in points]

#Adding the input points to the plot to visualize them
plt.scatter(x, y)

if os.path.exists(output_file):
    convexHullX = [x[i] for i in convex_hull_indices]
    convexHullY = [y[i] for i in convex_hull_indices]

    # Adding points of the convex hull to the plot
    plt.plot(convexHullX, convexHullY)

else
    print("No output file detected. Only showing the point set.")

plt.show()