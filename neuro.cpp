#include <iostream>
#include <vector>
#include <time.h> 
#include <random>
#include "defines.h"

using namespace std;

ostream& operator<<(ostream &out, const vector<double> &v) {
  cout << "[";
  for (size_t i = 0; i < v.size() - 1; i++)
    cout << v[i] << ", ";
  cout << v[v.size() - 1] << "]";
  return out;
}

ostream& operator<<(ostream &out, const vector<vector<double>> &v) {
  cout << "[";
  for (size_t i = 0; i < v.size() - 1; i++)
    cout << v[i] << ",\n ";
  cout << v[v.size() - 1] << "]";
  return out;
}

double rand_double(double min, double max) {
  static default_random_engine engine{static_cast<long unsigned int>(time(0))};
  uniform_real_distribution<double> rand(min, max);
  return rand(engine);
  // return min + (double) rand() / (double) RAND_MAX * (max - min);
}

class NeuroNet {
  private:
    vector<vector<double>> layers;
    vector<vector<vector<double>>> weights;
    // [номер матрицы][номер входного слоя][номер выходного слоя]

  public:
    NeuroNet(vector<size_t> layer_sizes, bool add_bias = false, bool fill_random = false) {
      layers.resize(layer_sizes.size());
      weights.resize(layers.size() - 1);

      for (size_t i = 0; i < layers.size(); i++) {
        layer_sizes[i] += (add_bias & (i + 1 != layers.size()));
        layers[i].resize(layer_sizes[i]);
      }

      for (size_t i = 0; i < weights.size(); i++) {
        weights[i].resize(layer_sizes[i]);
        for (size_t j = 0; j < layer_sizes[i]; j++) {
          weights[i][j].resize(layer_sizes[i + 1]);
          if (fill_random) {
            for (size_t k = 0; k < layer_sizes[i + 1]; k++) {
              weights[i][j][k] = rand_double(-1, 1);
            }
          }
        }
      }
    }

    void print() {
      for (size_t i = 0; i < layers.size(); i++) {
        cout << "layer " << i << ":\n";
        cout << layers[i] << endl << endl;
        if (i < layers.size() - 1) {
          cout << "weights " << i << "-" << i+1 << ":\n";
          cout << weights[i] << endl << endl;
        }
      }
    }
};

int main() {
  NeuroNet net({2, 4, 4, 3}, ADD_BIAS, FILL_RANDOM);
  net.print();
}