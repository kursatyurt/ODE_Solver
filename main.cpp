 #include <iostream>
 #include<vector>
 #include<cmath>


//Function of the ODE 
double ode(double a){
     double x;
     x = 9.81 -(1.229*3.14*1.15/(2*100)) * std::pow(a,2)  ; // Insert the ODE here
     return x;
 }    

int main(int argc, char *argv[]){
double dt = 0.1; // Step Size for the solver
double finaltime = 10; // Final Time for the solver
double time;
std::vector<double> velocity {0.0}; // Solution Vector

time = 0.0; // Initialize Time 
//Solution Loop for Explicit Euler
while (time < finaltime){
    double veln = velocity.back() + ode(velocity.back()) * dt;
    velocity.push_back(veln);
    time += dt;
 }

 
time=0.0; //Initialize Time for Output 
//Output loop that print  Time and Velocity to Screen
    for(int n : velocity) {
        std::cout << time << '\b' << n << '\n';
        time += dt;
    }
    return 0;
 }
