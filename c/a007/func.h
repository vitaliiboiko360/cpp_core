

void fibonacci(int first, int second, int limit)
{
    if(limit < 0)
        return;
    
    printf("%d ", first+second);
    return fibonacci(second, first+second, limit-1);
}

void fibonacci2(int first, int second, int limit)
{
    if(limit < 0)
    {
        printf("%d ", second);
        return;
    }
    printf("%d ", first);
    return fibonacci2(second, first+second, limit-1);
}