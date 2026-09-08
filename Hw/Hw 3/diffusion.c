#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n)
{
	int x = 0,y=0,z = 0;
	for(int i=0; i < n; i++){
		
		int a = rand() % 6;
		if(a == 0){
			x--;
		}
		if(a == 1){
			x++;
		}
		if(a == 2){
			y--;
		}
		if(a == 3){
			y++;
		}
		if(a == 4){
			z--;
		}
		if(a == 5){
			z++;
		}
	
	}
	int size = 2*n + 1;
	int xs = x + n;
	int ys = y + n;
	int zs = z + n;

    int index = xs * size * size + ys * size + zs;
	grid[index]++;
	

}

//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r)
{

	int size = 2*n + 1;
    int total = size * size * size;

    double rn = r * n;
    double rn2 = rn * rn;

    long inside = 0;
    long total_particles = 0;

	for(int i = 0; i<total;i++){
		int xs = i / (size * size);
        int ys = (i / size) % size;
        int zs = i % size;

        int x = xs - n;
        int y = ys - n;
        int z = zs - n;

        int dist2 = x*x + y*y + z*z;

        if(dist2 <= rn2)
            inside += grid[i];

        total_particles += grid[i];
	}
	return (double)inside / total_particles;
    
}

//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
	int size = 2*n+1;
	int total = size*size*size;
	int *grid = malloc(total*sizeof(int));
	for(int i = 0; i < total; i++){
    grid[i] = 0;}

	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below
	free(grid);

}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}
