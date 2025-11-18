#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <cmath>

struct InputParameter {
    int motor_speed;
};

struct ControlRule {
    int rule_value;
};

long long get_time_us() {
    using namespace std::chrono;
    return static_cast<long long>(duration_cast<microseconds>(
        steady_clock::now().time_since_epoch()
    ).count());
}

bool computeControlRule(const InputParameter* motor_state, ControlRule* rule) {
    // Simple PI controller demo:
    // - motor_state->motor_speed is treated as the measured process variable
    // - setpoint is a constant for this demo
    // - integral is kept across calls so controller state evolves
    static double integral = 0.0;
    static double last_error = 0.0;

    const double setpoint = 100.0; // desired motor speed
    const double Kp = 0.8;        // proportional gain
    const double Ki = 0.1;        // integral gain
    // approximate sample time (s) — adapt to your call frequency if known
    const double dt = 0.001;

    double measurement = static_cast<double>(motor_state->motor_speed);
    double error = setpoint - measurement;
    integral += error * dt;

    double u = Kp * error + Ki * integral;

    // Non-linear shaping to make the calculation a bit more realistic
    double shaped = std::tanh(u / 100.0) * 100.0;

    // round to nearest integer command and clamp to a reasonable range
    int cmd = static_cast<int>(std::lround(shaped));
    
    rule->rule_value = cmd;
    last_error = error;

    return true;
}


template<typename Callable>
double computeAverageTime(Callable function_to_measure,  const int n_iterations) {
    const auto start_time = get_time_us();
    for (int i = 0; i < n_iterations; ++i) {
        function_to_measure();
    }
    const auto end_time = get_time_us();
    return static_cast<double>(end_time - start_time) / static_cast<double>(n_iterations);
}


bool applyControlRuleWithPrintf(const InputParameter* motor_state) {
    bool is_rule_successfully_computed = false;
    ControlRule control_rule;
    
    printf("applyControlRule - Start: %lld us\n", get_time_us());
    is_rule_successfully_computed = computeControlRule(motor_state, &control_rule);
    
    printf("applyControlRule - End: %lld us\n", get_time_us());
    return is_rule_successfully_computed;
}

bool applyControlRule(const InputParameter* motor_state) {
    bool is_rule_successfully_computed = false;
    ControlRule control_rule;
    
    is_rule_successfully_computed = computeControlRule(motor_state, &control_rule);
    
    return is_rule_successfully_computed;
}


int main() {
    InputParameter motor_state{42};
    const int n_iterations = 10000;
    bool unused_output = false;

    const auto function_without_printf = [&]() {
        unused_output = applyControlRule(&motor_state);
        static_cast<void>(unused_output);
    };

    const auto function_with_printf = [&]() {
        unused_output = applyControlRuleWithPrintf(&motor_state);
        static_cast<void>(unused_output);
    };

    const auto avg_no_printf = computeAverageTime(function_without_printf, n_iterations);
    const auto avg_printf = computeAverageTime(function_with_printf, n_iterations);
    
    std::cout << "==========================\n";
    std::cout << "Average time without printf:\t" << avg_no_printf << " us" << "\nAverage time WITH print:\t" << avg_printf << " us.\n";
    std::cout << "--------------------------\n";
    std::cout << "Difference:\t\t\t" << avg_printf - avg_no_printf << " us.\n\n";


    return 0;
}
