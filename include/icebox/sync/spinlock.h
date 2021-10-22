#pragma once

//!
//! Represents a simple spinlock.
//!
struct spinlock {
    atomic_flag __flag;
};

//!
//! Create a new spinlock.
//!
#define NEW_SPINLOCK {              \
    .__flag = ATOMIC_FLAG_INIT      \
    }                               \


//!
//! Get the lock.
//!
void sl_lock(struct spinlock*);

//!
//! Release the lock.
//!
void sl_release(struct spinlock*);

