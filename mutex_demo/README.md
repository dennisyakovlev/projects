# Pthread Mutex's
Play around with pthread mutex locks.

## Notes:
Notice how the mutex locks. It locks for the entire duration of the write to the vector. Thus, the vector will be half filled with size/2 consecutive 1's and 2's. Whether 1 or 2 fills the first/second half may change, but it will always have them be conescutive.
