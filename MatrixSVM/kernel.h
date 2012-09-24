double*K=NULL;
int l=-1;

double custom_kernel(KERNEL_PARM *kernel_parm, SVECTOR *a, SVECTOR *b) 
     /* plug in you favorite kernel */                          
{
	if(l==-1){
		l=kernel_parm->poly_degree;
		K=malloc(l*l*sizeof(double));
		int i;
		int b;
		char b1;
		int j;
		FILE*f=fopen(kernel_parm->custom,"r");
		fscanf(f,"%c",&b1);
		for(i=0;i<l;i++)
			fscanf(f,"%i",&b);
		for(i=0;i<l;i++){
			fscanf(f,"%i",&b);
			for(j=0;j<l;j++){
				fscanf(f,"%lf",K+i+j*l);
			}
		}
		fclose(f);
		printf("Matrix is loaded, %i x %i.\n",l,l);
	}
	int i=atoi(a->userdefined);
	int j=atoi(b->userdefined);
	double k=K[i+j*l];
	/*printf("%i %i %lf\n",i,j,k);*/
	return k;
}
