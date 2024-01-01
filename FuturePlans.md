# Future Plans

## Optimisation
<hr>

Currently the main aspect of my project, that requires optimisation, is the memory usage. At the moment the string used to construct the L-System as well as all data defining points is being held in memory even after it is no longer needed. This problem becomes more apparent as the number of recursions increases due to the fact that the data created will increase in size exponentially. In order to fix this I will look into techniques to destroy variables from memory when they are no longer in use.

## Expanded Visual Intrigue
<hr>

