# Autor: Kano10

import csv

def parse_massif_file(input_file, output_file):
    # Prepare data to write to CSV
    csv_data = [['n', 'total']]  # Header for the CSV

    # Variables to store snapshot and memory values
    snapshot = None
    mem_heap = 0
    mem_extra = 0

    # Open and read the input file
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Parse the file and extract the relevant data
    for line in lines:
        if line.startswith('snapshot='):
            # When we encounter a new snapshot, calculate the total for the previous one
            if snapshot is not None:
                total_mem = mem_heap + mem_extra
                csv_data.append([snapshot, total_mem])

            # Update the snapshot number
            snapshot = int(line.split('=')[1])
            mem_heap = 0
            mem_extra = 0
        
        elif line.startswith('mem_heap_B='):
            mem_heap = int(line.split('=')[1])

        elif line.startswith('mem_heap_extra_B='):
            mem_extra = int(line.split('=')[1])

    # Handle the last snapshot
    if snapshot is not None:
        total_mem = mem_heap + mem_extra
        csv_data.append([snapshot, total_mem])

    # Write the extracted data to the CSV
    with open(output_file, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerows(csv_data)

    print(f'CSV file created: {output_file}')

# Example usage
input_file = 'massif.out.6058'
output_file = 'sk_tam'

parse_massif_file(input_file, output_file)
