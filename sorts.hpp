namespace math_tools {
    template<class T>
    void bubble_sort(T* start, T* end) {
        T* max_ptr = end;
        while (max_ptr != start) {
            T* max_ptr_itr = start;
            for (T* i = start + 1; i <= max_ptr; i++) {
                T* prev = i - 1;
                if (*prev > *i) {
                    T tmp = *prev;
                    *prev = *i;
                    *i = tmp;
                    max_ptr_itr = i;
                }
            }
            max_ptr = max_ptr_itr;
        }
    }

    template<class T>
    void selection_sort(T* start, T* end) {
        for (T* i = start; i < end; i++) {
            T *min = i;
            for (T* j = i + 1; j <= end; j++) {
                if (*j < *min) {
                    min = j;
                }
            }
            if (min != i) {
                T tmp = *i;
                *i = *min;
                *min = tmp;
            }
        }
    }

    template<class T>
    void insertion_sort(T* start, T* end) {
        for (T* i = start + 1; i <= end; i++) {
            T* last_sorted = i - 1;
            while (last_sorted >= start && *last_sorted > *(last_sorted + 1)) {
                T tmp = *last_sorted;
                *last_sorted = *(last_sorted + 1);
                *(last_sorted + 1) = tmp;
                last_sorted--;
            }
        }
    }

    template<class T>
    void fast_sort(T* start, T* end) {
        
    }

    
}