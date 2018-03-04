#include "../types.h"
#include "../defs.h"
#include "../param.h"
#include "../mmu.h"
#include "proc.h"

/*               MIN HEAP EXAMPLE
 *
 *                     [1]
 *                     / \
 *                    /   \
 *                   /     \
 *                  /       \
 *                 /         \
 *                [2]        [3]
 *               /  \        / \
 *              /    \      /   \
 *            [4]    [5]  [6]   [7]
 *            / \
 *           /   \
 *         [8]   [9]
*/

int size = 0;

struct proc *heap[NPROC];

/*Index of left child node of p */
int lc(int p) { return 2 * p + 1; }

/*Index of right child node of p */
int rc(int p) { return 2 * p + 2; }

/*Index of parent node of c */
int p(int c) { return (c - 1) / 2; }

/*Check if node has left child */
int has_lc(int node) { return lc(node) < size; }

/*Check if node has right child */
int has_rc(int node) { return rc(node) < size; }

/*Check if node has parent */
int has_p(int node) { return p(node) >= 0; }

/*Left child value of node */
double lc_val(int node) { return heap[lc(node)]->pr; }

/*Right child value of node */
double rc_val(int node) { return heap[rc(node)]->pr; }

/*Parent value of node */
double p_val(int node) { return heap[p(node)]->pr; }

/*Current value of node */
double c_val(int node) { return heap[node]->pr; }

/*Exchange of nodes */
void swap(int a, int b) {
    struct proc *p = heap[a];
    heap[a] = heap[b];
    heap[b] = p;
}

/* Checks for the need to exchange the node with one of their child.
 * This process stops when the node stops having children smaller than that. */
void rec_to_end(int node) {
    if (has_lc(node)) {
        int min_c = lc(node);
        if (has_rc(node) && rc_val(node) < lc_val(node))
            min_c = rc(node);
        if (c_val(node) < c_val(min_c))
            return;
        else
            swap(node, min_c);
        rec_to_end(min_c);
    }
}

/* Pop of the root node,
 * move the last node to the beginning of the HEAP (root) and finally
 * call rec_to_root (0) to place it in the correct position! */
struct proc *min_heap_pop() {
    if (size < 1)
        return 0;
    struct proc *p = heap[0];
    heap[0] = heap[--size];
    rec_to_end(0);
    p->mhi = -1;
    return p;
}

/* Checks for the need to exchange the new node with his father.
 * This process will stop when the new node becomes an orphan or
 * when his father stops being greater than him. */
int rec_to_root(int new) {
    if (has_p(new) && p_val(new) > c_val(new)) {
        int parent = p(new);
        swap(parent, new);
        return rec_to_root(parent);
    }
    return new;
}

/* Insert a new process into the HEAP.
 * The push to be successful, there should be free space in the HEAP.
 * First, the new node enters at the end of the HEAP,
 * The rec_to_root(size) function assumes to place the new node in the correct position
 * of the HEAP.
 * Finally, the HEAP size is increased by one and returned! */
int min_heap_push(struct proc *p) {
    if (size > NPROC)
        return 0;
    heap[size] = p;
    p->mhi = rec_to_root(size);
    return ++size;
}

int min_heap_heapify(int node) {
    if (node >= size)
        return 0;
    if (has_p(node) && p_val(node) > c_val(node))
        rec_to_root(node);
    else if (has_lc(node))
        rec_to_end(node);
    return 1;
}
