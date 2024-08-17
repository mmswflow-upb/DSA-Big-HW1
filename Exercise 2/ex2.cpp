#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<string> split(string x, int size) {

    vector<string> res;
    res.resize(size);
    size_t k = 0;
    int i = 0;

    while (x.length() != 0) {

        k = x.find(",", 0);
    
        if (k == string::npos) {

            res[i] = x.substr(0, x.length());
            break;
        }

        res[i] = x.substr(0, k);
        x = x.substr(k + 1, x.length() - k);
        i++;
    }

    return res;

}

struct Order {
    int t, d; // arrival time and duration
};

int main() {

    while (true) {
        int N, T, k;
        
        string path;
        cout << "\n\nInsert a path to text file: ";
        cin >> path;
        cout << "\n";

        queue<Order> orders;
        
        //Read the maximum number of orders and closing time.
        string line;
        ifstream fileReader(path);

        getline(fileReader, line);
        vector<string> data = split(line,2);

        N = stoi(data[0]);
        T = stoi(data[1]);
        k = N;

        // Read the orders
        while(getline(fileReader, line) && k>=0) {
            if (line.empty()) {
                continue;
            }
            Order order;
            data = split(line, 2);
            order.t = stoi(data[0]);
            order.d = stoi(data[1]);
          
            orders.push(order);

            k--;
        }

        int max_duration = 0;
        int current_time = 0;
       
        // Process the orders
        while (!orders.empty()) {
            Order order = orders.front();
            orders.pop();

            // Compute theoretical completion time
            int theoretical_completion_time = order.t + order.d;

            // Compute actual completion time
            int actual_completion_time =  max(current_time, order.t) + order.d;

            // Update max_duration
            max_duration = max(max_duration, order.d);

            // Check if the order is completed before closing time
            if (actual_completion_time <= T) {
                cout << "Order " << (N - orders.size()) << ": expected completion time = " << theoretical_completion_time << ", actual completion time = " << actual_completion_time << endl;
                current_time = actual_completion_time;

                // Check if the chef can take a break
                if (current_time < orders.front().t) {
                    
                    cout << "The chef takes a break from " << current_time << " to " << min(T,orders.front().t) << endl;
                   
                }
            }
            // Check if the order is completed after closing time
            else {
                cout << "Order " << (N - orders.size()) << " cannot be completed before closing time." << endl;
            }
            cout << "\n";
        }

        // Check if there are orders completed after closing time
        if (current_time > T) {
            cout << "Some orders are completed after closing time." << endl;
        }

        // Print the maximum duration our chef has to work on a single order
        cout << "Maximum duration our chef has to work on a single order: " << max_duration << endl;
    }
}