int NumCmp( const void *FirstArg, const void *SecondArg )
{
	int ReturnValue;
	int First = *(int *)FirsArg;
	int Second = *(int *)SecondArg;

	if ( First < Second )
	{
		ReturnValue = -1;
	}
	else if ( First == Second )
	{
		ReturnValue = 0;
	}
	else
	{
		ReturnValue = 1;
	}

	return ReturnValue;

}
