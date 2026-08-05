
# Introduce
short

# quick start example

# Running emus
## comandline
## MPI commdline
## inifile

# Making capabilties emu-able

To declare a gambit function as emulatable for a given capability, the macro START_FUNCTION_EMULATABLE(return type) within the rollcall header entry is required (as opposed to the standard START_FUNCTION(return type) declaratation).

```
  #define FUNCTION function_name           // Name of an observable function: floating-point number of events in some hypothetical process
    START_FUNCTION_EMULATABLE(double)       // Declare that this function calculates a double precision variable
  #undef FUNCTION
```

## Defining Translation functions
## Defining Threshold function (optional)

# making emu
## overview
## Python Plugin
## c interface (enter at own risk)
