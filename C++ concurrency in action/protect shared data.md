1. mutex, the most common way by adding lock.
2. some data is read-only, then we only need to add lock during initialisating, and after that the data will not be modified at all thus lock is not needed.
3. 
