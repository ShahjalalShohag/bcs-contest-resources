import os
import shutil
import re

"""
This script is used to move the accepted solutions from the problems directory (generated from Polygon) to the target directory.
"""

POLYGON_PROBLEMS_DIR = "problems"  # Source directory containing polygon problem folders
TARGET_DIR = "aust_iupc_2025"  # Target directory to move the accepted solutions


def read_desc_file(desc_path):
    """Read the .desc file and extract the tag"""
    try:
        with open(desc_path, "r") as f:
            content = f.read()
            # Find the Tag line using regex
            match = re.search(r"Tag:\s*(.*)", content)
            if match:
                return match.group(1).strip()
    except Exception as e:
        print(f"Error reading desc file {desc_path}: {e}")
    return None


def process_solutions(problems_dir, target_dir):
    """Process all problem folders and move qualifying solutions"""

    # Create target directory if it doesn't exist
    os.makedirs(target_dir, exist_ok=True)

    # Iterate through each problem folder (A, B, C, etc.) in sorted order
    for problem in sorted(os.listdir(problems_dir)):
        print("Processing problem:", problem)
        problem_path = os.path.join(problems_dir, problem)
        if not os.path.isdir(problem_path):
            continue

        solutions_path = os.path.join(problem_path, "solutions")
        if not os.path.exists(solutions_path):
            continue

        # Create problem folder in target directory
        target_problem_dir = os.path.join(target_dir, problem)
        os.makedirs(target_problem_dir, exist_ok=True)

        # Process each solution in the solutions directory
        for file in os.listdir(solutions_path):
            if file.endswith(".desc"):
                desc_path = os.path.join(solutions_path, file)
                cpp_path = os.path.join(solutions_path, file[:-5])

                # Check if corresponding .cpp file exists
                if not os.path.exists(cpp_path):
                    continue

                # Read tag from desc file
                tag = read_desc_file(desc_path)

                # Move file if tag is MAIN or ACCEPTED
                if tag in ["MAIN", "ACCEPTED"]:
                    # Use main_solution name if tag is MAIN, otherwise use original filename
                    target_filename = (
                        "main_solution.cpp" if tag == "MAIN" else file[:-5]
                    )
                    target_file = os.path.join(target_problem_dir, target_filename)
                    try:
                        shutil.copy2(cpp_path, target_file)
                        print(f"Moved solution: {cpp_path} -> {target_file}")
                    except Exception as e:
                        print(f"Error moving file {cpp_path}: {e}")


def main():
    process_solutions(POLYGON_PROBLEMS_DIR, TARGET_DIR)
    print("Processing completed!")


if __name__ == "__main__":
    main()
