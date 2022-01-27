#include "gambit/Backends/function_return_utils.hpp"

// Function used to return pointer-to-wrapper
template<typename U, typename V>
U* pointer_returner(V* ptr)
{
    if (ptr->is_wrapped())
    {
        return (ptr->wrapper__BOSS());
    }

    else
    {
        U* wptr = new U(ptr);
        ptr->can_delete_wrapper(true);
        return wptr;
    }
}


// Function used to return reference-to-wrapper
template<typename U, typename V>
U& reference_returner(V* ptr)
{
    if (ptr->is_wrapped())
    {
        return *(ptr->wrapper__BOSS());
    }

    else
    {
        U* wptr = new U(ptr);
        ptr->can_delete_wrapper(true);
        return *wptr;
    }
}

// Version of the above function taking a const input
template<typename U, typename V>
U& reference_returner(const V* ptr)
{
    if (ptr->is_wrapped())
    {
        return *(ptr->wrapper__BOSS());
    }

    else
    {
        U* wptr = new U(ptr);
        ptr->can_delete_wrapper(true);
        return *wptr;
    }
}

