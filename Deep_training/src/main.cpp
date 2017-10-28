
#include <iostream>
#include <vector>
#include <algorithm>

#include <blaze/Math.h>

#include <deepsea/math_util.h>
#include <deepsea/network_builder.h>
#include <deepsea/read_write_util.h>
#include <deepsea/prediction.h>

using namespace std;

//If uncommenting below FLAG, uncomment from read_write_util.h also
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

	//Declare training params
#ifndef BENCH
	int batch_size = 20;
	int nr_epoch = 50;
#else
  int batch_size = 50;
  int nr_epoch = 200;
#endif

	double learning_rate = 0.01;
	int nr_batch;

	//Initialize model and train graph parameters
	model_param m_p(layer);
	initialize_param(&m_p);

	forward_param f_p(layer, batch_size);
	backward_param b_p(layer, batch_size);

	//read datafile, seperate test data X_test, Y_test
  int *temp_label;
#ifndef BENCH
  DynamicMatrix<double> X_all = read_csv_modified("combined_data.csv", NR_DATA, INPUT_SIZE, &temp_label);
#else
  DynamicMatrix<double> X_all = read_csv_modified("letter-recognition.data", NR_DATA, INPUT_SIZE, &temp_label);
#endif
  DynamicMatrix<double> Y_all = get_label_modified(temp_label, NUM_CLASSES, NR_DATA);

  nr_batch = X_all.columns()/batch_size;


  //Allocate matrix variables to be used at training
  DynamicMatrix<double> X;
  DynamicMatrix<double> Y;

  DynamicMatrix<double> X_test;
  DynamicMatrix<double> Y_test;
  DynamicMatrix<double> O;

	//Start training
	for(int i=0;i<nr_epoch;i++){

		for(int j=0;j<nr_batch;j++){
			//Prepare input batch X and output label Y
			X = submatrix(X_all, 0, j*batch_size, INPUT_SIZE, batch_size);
			Y = submatrix(Y_all, 0, j*batch_size, NUM_CLASSES, batch_size);

			feed_forward(&m_p, &f_p, X);
			back_prop(&m_p, &f_p, &b_p, Y);
			gradient_descent(&m_p, &b_p, learning_rate);
		}

		//Print accuracy and cost on test data set, test set should be separated, but I am lazy :/
    X_test = submatrix(X_all, 0, 0, INPUT_SIZE, batch_size);
    Y_test = submatrix(Y_all, 0, 0, NUM_CLASSES, batch_size);
		O = predict(&m_p, &f_p, X_test);

		cout << "Cost for epoch " << i << " is " << mean_cross_entropy_loss(Y_test, O) << endl;
		cout << "Accuracy for epoch " << i << " is " << accuracy(Y_test, O) << endl << endl;
	}

#ifndef BENCH
	write_model(&m_p, "model_4.txt");
#else
	write_model(&m_p, "model_2.txt");
#endif
  return 0;
}
