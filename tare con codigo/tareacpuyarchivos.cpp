#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <cmath>

class CPULatencyBenchmark {
public:
static void run_comprehensive_test() {
std::cout << "=== BENCHMARK DE LATENCIA CPU ===" << std::endl;

std::cout << "\n1. Latencia de instrucciones:" << std::endl;
measure_cpu_instruction_latency();

std::cout << "\n2. Latencia de llamadas a función:" << std::endl;
measure_function_call_latency();

std::cout << "\n3. Latencia de diferentes niveles de cache:" << std::endl;
measure_different_cache_levels();

std::cout << "\n4. Latencia de acceso a memoria:" << std::endl;
measure_memory_latency();

std::cout << "\n5. Latencia de contexto:" << std::endl;
measure_context_switch_latency();
}


private:
/*static void measure_context_switch_latency() {
    const int iterations = 100000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++) {
        std::this_thread::yield();
        }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);

    std::cout << "Latencia cambio contexto: "
    << duration.count() / iterations << " ns" << std::endl;
    };*/



//latencia de instruciones(funcion 1)
    static void measure_cpu_instruction_latency() {
        const int iterations = 100000000;
        volatile int x = 0;

        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0 ; i < iterations; i++){
            x += 1;
        }

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast < std::chrono::nanoseconds > (end - start);
        std::cout <<"latencia por instruccion: "
        << (double)duration.count() / iterations
        <<" ns " << std::endl;
    }
//latencia de llamada a funcion vacia (funcion 2)
    static void empty_function() {  }

    static void measure_function_call_latency() {
        const int iterations = 100000000;

        auto start  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < iterations; i++) {   
            empty_function();
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
        std::cout   << "latencia por llamada a funcion: "
                    <<(double)duration.count() / iterations
                    << "ns" << std::endl;
    }
//latencia de cache(funcion 3)
static void measure_different_cache_levels() {
    const int sizes[] = {32 * 1024, 25 * 1024, 8* 1024* 1024, 6 * 1024 * 1024};
    const char* level_names[] = {"L1", "L2","L3", "RAM"};

    for (int i = 0; i < 4; i++) {
        size_t size = sizes[i];
        std::vector<int> data(size / sizeof(int));

        auto start = std::chrono::high_resolution_clock::now();
        volatile int sum = 0;
        for (size_t j = 0; j < data.size(); j++){
            sum += data[j];
        }
        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds > (end - start);
        std::cout   << "latencia estimada " << level_names[i]
                    << "; " << (double)duration.count() / data.size()
                    << " ns por acceso " <<  std::endl;
    }
}

//latencia  de acceso a meoria (funcion 4)

static void measure_memory_latency() {
    const int size = 100000000;
    std::vector<int>memory(size);
    for (int i = 0; i < size; i++) {
        memory[i] = rand () % size;
    }

    auto start = std::chrono::high_resolution_clock::now();
    volatile int index = 0 ;
    for (int i = 0; i < size; i++) {
        index = memory[index];
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast < std::chrono::nanoseconds > (end - start);
    std::cout   << "latencia promedio de acceso a memoria: "
                <<(double)duration.count() / size
                <<" ns" << std::endl;
}

//latencia de cambio de contexto (funcion 5)
static void measure_context_switch_latency() {
    const int iterations = 100000000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; i++){
        std::this_thread::yield();
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast < std::chrono::nanoseconds > (end - start);

    std::cout << "latencia cambio contexto: "
    << duration.count() / iterations << " ns" << std::endl;
}};


// Función para calcular la latencia del pipeline(funcion 6 la que se pide alo ultimo)
void measure_pipeline_latency() {
const int iterations = 100000000;
volatile int results[10];

auto start = std::chrono::high_resolution_clock::now();

// Operaciones dependientes que fuerzan serialización
int value = 1;
for (int i = 0; i < iterations; i++) {
value = value + 1; // op1
value = value * 2; // op2 (depende de op1)
value = value - 1; // op3 (depende de op2)
value = value / 2; // op4 (depende de op3)
results[i % 10] = value;
}

auto end = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);

std::cout << "Latencia pipeline (ops dependientes): "
<< duration.count() / (iterations * 4) << " ns por operación" << std::endl;
}

int main() {
std::cout << "Iniciando mediciones de latencia CPU..." << std::endl;

// Ejecutar benchmark completo
CPULatencyBenchmark::run_comprehensive_test();

// Medición adicional de pipeline
std::cout << "\n6. Latencia de pipeline:" << std::endl;
measure_pipeline_latency();

std::cout << "\n=== Mediciones completadas ===" << std::endl;

return 0;
}