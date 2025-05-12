import sys

# Set a higher recursion depth limit for potentially deep trees.
# The maximum N can be up to 3*10^5, which might exceed default Python limits.
try:
    # Get current recursion depth limit
    current_limit = sys.getrecursionlimit()
    # Set target limit slightly above maximum possible N
    target_limit = 300005 + 10 
    if current_limit < target_limit:
         sys.setrecursionlimit(target_limit)
except Exception as e:
    # In some environments setting recursion limit might fail.
    # Print a warning or proceed with caution.
    # print(f"Warning: Could not set recursion depth limit: {e}", file=sys.stderr)
    pass 

# Define the modulus for calculations
MOD = 998244353

def power(base, exp):
    """
    Computes (base^exp) % MOD efficiently using binary exponentiation.
    """
    res = 1
    base %= MOD
    while exp > 0:
        if exp % 2 == 1:  # If exponent is odd, multiply result with base
            res = (res * base) % MOD
        # Square the base and halve the exponent
        base = (base * base) % MOD
        exp //= 2
    return res

def modInverse(n):
    """
    Computes the modular multiplicative inverse of n modulo MOD.
    Uses Fermat's Little Theorem: n^(MOD-2) % MOD.
    Assumes MOD is a prime number and n is not divisible by MOD.
    """
    # Since MOD is prime, inverse exists for n % MOD != 0.
    # The constraints ensure n is a product of subtree sizes (1 to N),
    # N < MOD, so n % MOD is never 0.
    return power(n, MOD - 2)

# Use global lists for adjacency list and subtree sizes for efficiency.
# They will be re-initialized in compute_prod_subtree_sizes for each tree.
adj = []
subtree_size = []

def dfs_size(u):
    """
    Performs Depth First Search starting from node u to calculate subtree sizes recursively.
    Stores the size of the subtree rooted at u in the global `subtree_size` list.
    Returns the computed size for the subtree rooted at u.
    """
    # Initialize size for current node u (counts itself)
    size = 1 
    # Iterate over all children of u in the adjacency list
    for v in adj[u]:
        # Recursively call dfs_size for each child and add its subtree size
        size += dfs_size(v)
    # Store the computed size for node u in the global list
    subtree_size[u] = size
    return size

def compute_prod_subtree_sizes(N, parents):
    """
    Builds the tree structure from the parent array, computes all subtree sizes using DFS,
    and returns the product of all subtree sizes modulo MOD.
    """
    global adj, subtree_size # Indicate use of global variables

    # Initialize adjacency list and subtree size array for N nodes (indices 1 to N)
    adj = [[] for _ in range(N + 1)]
    # subtree_size could be initialized later, but doing it here ensures clean state
    subtree_size = [0] * (N + 1) 
    
    # Build the adjacency list (child list for each node) from the parent array.
    # The input `parents` array is 0-indexed. parents[i-1] gives the parent of node i.
    # We iterate through nodes 2 to N to establish parent-child relationships.
    for i in range(2, N + 1): 
        parent_node = parents[i-1] 
        child_node = i
        # Problem constraints state 1 <= a_i < i for i > 1. This means parent_node is always a valid node index >= 1.
        # Add child_node to the adjacency list of parent_node.
        adj[parent_node].append(child_node)

    # Start the DFS from the root (node 1) to compute sizes for all nodes in the tree.
    dfs_size(1)
    
    # Calculate the product of all computed subtree sizes modulo MOD.
    prod = 1
    for i in range(1, N + 1):
       # Since the graph is a tree rooted at 1 and all nodes are connected,
       # subtree_size[i] will be >= 1 for all i from 1 to N.
       # Also, subtree_size[i] <= N < MOD. Thus, subtree_size[i] % MOD != 0.
       # The product modulo a prime MOD will be non-zero.
       prod = (prod * subtree_size[i]) % MOD
    
    return prod

def solve():
    """
    Reads the input for a single test case, computes the required ratio, and prints the result.
    """
    N = int(sys.stdin.readline())
    # Read the parent arrays for tree A and tree B.
    A_parents = list(map(int, sys.stdin.readline().split()))
    B_parents = list(map(int, sys.stdin.readline().split()))

    # Compute the product of subtree sizes for tree A.
    prod_A = compute_prod_subtree_sizes(N, A_parents)
    # Compute the product of subtree sizes for tree B.
    prod_B = compute_prod_subtree_sizes(N, B_parents)

    # Compute the modular inverse of prod_A.
    inv_prod_A = modInverse(prod_A)
    
    # The required ratio r is (prod_B / prod_A) % MOD.
    # Calculate this as (prod_B * inv_prod_A) % MOD.
    result = (prod_B * inv_prod_A) % MOD
    print(result)


# Main execution part of the script.
# Read the number of test cases.
T = int(sys.stdin.readline())
# Process each test case.
for _ in range(T):
    solve()