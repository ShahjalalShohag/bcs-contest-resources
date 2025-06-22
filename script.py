import os
import shutil
import re

"""
This script is used to move the accepted solutions from the problems directory (generated from Polygon) to the target directory.
"""

# == START CONFIG == #
POLYGON_PROBLEMS_DIR = "problems"  # Source directory containing polygon problem folders (can be downloaded from Polygon by clicking on "Download Package")
TARGET_DIR = "uu_iupc_2025"  # Target directory to move the accepted solutions
PROBLEM_NAMES = """
A. Edgy Graph
B. Red Dead Redemption 2
C. Binomial XOR
D. Symmetric Swap
E. The Perfect Spider Web
F. Divisible Perfection
G. MEX-imum Beauty
H. Substring Symphony
I. Statue on a Permutation
J. Sublime Replacement
K. Math Madness
"""
# == END CONFIG == #

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

    # Create a mapping of problem names to indices
    problem_mapping = {}
    for line in PROBLEM_NAMES.strip().split('\n'):
        if not line.strip():
            continue
        index, name = line.split('. ', 1)
        problem_mapping[name.strip()] = index.strip()

    # Iterate through each problem folder
    for problem in sorted(os.listdir(problems_dir)):
        problem_path = os.path.join(problems_dir, problem)
        if not os.path.isdir(problem_path):
            continue

        # Try to find the problem name in the name.tex file
        name_tex_path = os.path.join(problem_path, 'statement-sections', 'english', 'name.tex')
        if not os.path.exists(name_tex_path):
            continue

        with open(name_tex_path, 'r') as f:
            problem_name = f.read().strip()
            if problem_name not in problem_mapping:
                print(f"Warning: Problem name '{problem_name}' not found in mapping, skipping")
                continue

            # Get the index for this problem
            problem_index = problem_mapping[problem_name]
            print(f"Processing problem {problem_index}: {problem_name}")

            solutions_path = os.path.join(problem_path, "solutions")
            if not os.path.exists(solutions_path):
                continue

            # Create problem folder in target directory using the index
            target_problem_dir = os.path.join(target_dir, problem_index)
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
                    if tag == "MAIN":
                        tag = "[MAIN_SOLUTION]"
                    # Prepend the tag to the filename
                    target_filename = f"[{tag}] {file[:-5]}"
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
