#include <stdio.h>

#define TEST_ARRAY_LEN 5
static const int TEST_ARRAY[TEST_ARRAY_LEN] = {1, 3, 6, 8, 10};
#define TEST_ARRAY_LEN2 6
static const int TEST_ARRAY2[TEST_ARRAY_LEN2] = {1, 3, 4, 6, 8, 10};

/* Returns the index of x in arr. If it doesn't exist, returns some arbitrary
 * value.
 */
int bin_search(const int *arr, int l, int r, int x)
{
    if (l == r)
        return l;

    int mid = l + ((r - l) / 2);
    if (arr[mid] > x)
        return bin_search(arr, l, mid - 1, x);
    else if (arr[mid] < x)
        return bin_search(arr, mid + 1, r, x);
    else
        return mid;
}

int main(int argc, char *argv[])
{
    printf("%d\n", bin_search(TEST_ARRAY, 0, TEST_ARRAY_LEN, 10));
    printf("%d\n", bin_search(TEST_ARRAY2, 0, TEST_ARRAY_LEN2, 10));
}
