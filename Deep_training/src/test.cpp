#include <iostream>
#include <vector>
#include <algorithm>

#include <blaze/Math.h>

#include <deepsea/math_util.h>
#include <deepsea/network_builder.h>
#include <deepsea/read_write_util.h>
#include <deepsea/prediction.h>

using namespace std;

//#define BENCH 0

#ifndef BENCH
#define INPUT_SIZE 784
#define NUM_CLASSES 4
#define NR_DATA 409
#else
#define INPUT_SIZE 16
#define NUM_CLASSES 26
#define NR_DATA 20000
#endif

int main()
{
#ifndef BENCH
	static const int arr[] = {INPUT_SIZE, 1024, 100, 150, 20, NUM_CLASSES};
#else
  static const int arr[] = {INPUT_SIZE, 20, 40, NUM_CLASSES};
#endif
	vector<int> layer (arr, arr + sizeof(arr)/sizeof(arr[0]));

	//Declare params
#ifndef BENCH
	int batch_size = 1;
#else
  int batch_size = 10;
#endif
	int nr_batch;

#ifndef BENCH
  model_param m_p = read_model("model_4.txt");
#else
	model_param m_p = read_model("model_2.txt");
#endif
	forward_param f_p(layer, batch_size);

	//read datafile
  int *temp_label;
#ifndef BENCH
  DynamicMatrix<double> X_all = read_csv_modified("combined_data.csv", NR_DATA, INPUT_SIZE, &temp_label);
#else
  DynamicMatrix<double> X_all = read_csv_modified("letter-recognition.data", NR_DATA, INPUT_SIZE, &temp_label);
#endif
  DynamicMatrix<double> Y_all = get_label_modified(temp_label, NUM_CLASSES, NR_DATA);

  //nr_batch = X_all.columns()/batch_size;
  nr_batch = 2;


  //Allocate matrix variables to be used
  DynamicMatrix<double> X;
  DynamicMatrix<double> Y;
  DynamicMatrix<double> O;

	for(int i=0;i<nr_batch;i++){
		//Prepare input batch X and output label Y
		X = submatrix(X_all, 0, i*batch_size, INPUT_SIZE, batch_size);
		Y = submatrix(Y_all, 0, i*batch_size, NUM_CLASSES, batch_size);
    cout << X << endl;
    cout << Y << endl;

		O = predict(&m_p, &f_p, X);
    cout << O << endl;
    cout << "Accuracy for batch " << i << " is " << accuracy(Y, O) << endl << endl;
	}
  f_p.print_linear();
  return 0;
}
