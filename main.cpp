 #include <iostream>
 #include<vector>
 #include<cmath>



double ode(double a){
     double x;
     x = 9.81 -(1.229*3.14*1.15/(2*100)) * std::pow(a,2)  ; // Insert the ODE here
     return x;
 }    

 int main(int argc, char *argv[]){
double dt = 0.1; // Step Size for the solver
double finaltime = 10; // Final Time for the solver
double time;
std::vector<double> velocity {0.0};


while (time < finaltime){
    double veln = velocity.back() + ode(velocity.back()) * dt;
    velocity.push_back(veln);
    time += dt;
 }



    for(int n : velocity) {
        std::cout << n << '\n';
    }
    return 0;
 }