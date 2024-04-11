import math
import random
import pandas as pd

def haversine(lat1, long1, lat2, long2):
    radiusOfEarthInMiles = 3958.8
    lat1Radians = math.radians(lat1)
    long1Radians = math.radians(long1)
    lat2Radians = math.radians(lat2)
    long2Radians = math.radians(long2)
    a = pow(math.sin((lat2Radians-lat1Radians)/2), 2) + math.cos(lat1Radians)*math.cos(lat2Radians)*pow(math.sin((long2Radians-long1Radians)/2), 2)
    c = 2*math.atan2(math.sqrt(a), math.sqrt(1-a))
    return radiusOfEarthInMiles * c

def rand_partition(arr, p, r):
    pivot_index = random.randint(p, r)
    arr[r], arr[pivot_index] = arr[pivot_index], arr[r]
    pivot = arr[r]['distance']
    i = p - 1
    for j in range(p, r):
        if arr[j]['distance'] <= pivot:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i + 1], arr[r] = arr[r], arr[i + 1]
    return i + 1

def rand_select(arr, p, r, i):
    if p == r:
        return arr[p]
    q = rand_partition(arr, p, r)
    k = q - p + 1
    if i == k:
        return arr[q]
    elif i < k:
        return rand_select(arr, p, q - 1, i)  # Corrected parameter here
    else:
        return rand_select(arr, q + 1, r, i - k)  # Corrected parameter here

def read_store_data(file_name):
    data = pd.read_excel(file_name)
    store_data = []
    for _, row in data.iterrows():
        store = {
            'id': row['Store #'],
            'address': row['Address'],
            'city': row['City'],
            'state': row['State'],
            'zipCode': row['Zip Code'],
            'latitude': row['Latitude'],
            'longitude': row['Longitude'],
            'distance': -1
        }
        store_data.append(store)
    return store_data

def process_queries(store_data, query_data):
    for query in query_data:
        try:
            lat_query, long_query, num_stores_to_find = query
            lat_query = float(lat_query)
            long_query = float(long_query)
            num_stores_to_find = int(num_stores_to_find)
        except ValueError as ve:
            print(f"Error processing query data: {ve}")
            continue

        # Compute distances to all stores
        for store in store_data:
            store['distance'] = haversine(lat_query, long_query, store['latitude'], store['longitude'])

        # Ensure num_stores_to_find is valid
        num_stores_to_find = min(num_stores_to_find, len(store_data))

        # Find the nth closest store using rand_select
        if num_stores_to_find > 0:
            nth_closest_store = rand_select(store_data, 0, len(store_data) - 1, num_stores_to_find)  # Corrected parameter here
            if not nth_closest_store:
                print("Error: Number of stores desired is greater than the number of available stores.")
                continue
        else:
            print("Error: Number of stores desired should be greater than zero.")
            continue

        # Find all stores that are at least as close as the nth closest store
        closest_stores = [store for store in store_data if store['distance'] <= nth_closest_store['distance']]

        # Sort the closest stores based on their distances
        closest_stores.sort(key=lambda x: x['distance'])

        # Print the closest stores
        print(f"The {len(closest_stores)} closest Stores to ({lat_query}, {long_query}):")
        for store in closest_stores:
            print(f"Store #{store['id']}. {store['address']}, {store['city']}, {store['state']}, {store['zipCode']}. - {store['distance']:.2f} miles.")
        print()

def main():
    whataburger_store_data_file = "WhataburgerData.xlsx"
    starbucks_store_data_file = "StarbucksData.xlsx"
    query_file = "Queries.xlsx"

    # Read the WhataBurger store data from the Excel file
    whataburger_store_data = read_store_data(whataburger_store_data_file)

    # Read the Starbucks store data from the Excel file
    starbucks_store_data = read_store_data(starbucks_store_data_file)

    # Read the query data from the Excel file
    query_data = pd.read_excel(query_file, header=None).values.tolist()

    # Process the queries for Whataburger stores
    print("Whataburger store data:")
    process_queries(whataburger_store_data, query_data)

    # Process the queries for Starbucks stores
    print("\nStarbucks store data:")
    process_queries(starbucks_store_data, query_data)

if __name__ == "__main__":
    main()
