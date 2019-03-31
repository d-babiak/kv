### Map
+ Change pthread_mutex to pthread_rwlock 

```
pthread_rwlock_destroy 
pthread_rwlock_init

pthread_rwlock_rdlock

pthread_rwlock_tryrdlock

pthread_rwlock_trywrlock

pthread_rwlock_unlock 
pthread_rwlock_wrlock

pthread_rwlockattr_destroy

pthread_rwlockattr_getpshared

pthread_rwlockattr_init
```

+ What happens if a thread with a read lock tries to acquire a write lock? 

### Networking
+ Gossip protocol
+ Try version with UDP
 
### Persistence
+ Append-only log of the CLI commands

### Encoding
+ I like https://redis.io/topics/protocol
+ Guess we make our own
