/*********************************************************************
 *  Indirect priority queue.
 *
 *  A priority queue that can store items named 0, 1, ..., MAXN.
 *  The priority of item i is given by priority[i]. The client
 *  has access to priority[]. If the client changes priority[i],
 *  it is the client's responsibility to call PQchange(i).
 *
 *  This code is from "Algorithms in C, Third Edition,
 *  by Robert Sedgewick, Addison-Wesley, 2002.
 *********************************************************************/

/*********************************************************************
 *  Initialze a PQ with up to MAXN elements. Use priority[] as
 *  the array of real-valed priorities.
 ********************************************************************/
void PQinit(int MAXN, double priority[]);

/*********************************************************************
 *  Return 1 if the PQ is empty, 0 otherwise.
 *********************************************************************/
 int PQisempty(void);

/*********************************************************************
 *  Insert element with index i and priority = priority[i] into the PQ.
 *********************************************************************/
void PQinsert(int i);

/*********************************************************************
 *  Delete and return the item with the smallest priority.
 *********************************************************************/
 int PQdelmin(void);

/*********************************************************************
 *  Tell the PQ that the priority of i changed.
 *********************************************************************/
void PQchange(int i);
