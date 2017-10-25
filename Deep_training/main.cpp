#include <iostream>
#include <vector>
#include <algorithm>

#include <deepsea/math_util.h>
#include <deepsea/network_builder.h>
#include <deepsea/read_write_util.h>
#include <deepsea/prediction.h>

#include <blaze/Math.h>


using namespace std;
int main()
{

	static const int arr[] = {};
	vector<int> layer (arr, arr + sizeof(arr)/sizeof(arr[0]));

	//Declare training params
	int batch_size;
	int nr_epoch;
	double learning_rate;
	int nr_batch;

	//Initialize model and train graph parameters
	model_param m_p(layer);
	initialize_param(&m_p);

	forward_param f_p(layer, batch_size);
	backward_param b_p(layer, batch_size);

	//read datafile, seperate test data X_test, Y_test

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
			X = submatrix(X_all);
			Y = submatrix(Y_all);

			feed_forward(&m_p, &f_p, X);
			back_prop(&m_p, &f_p, &b_p, Y);
			gradient_descent(&m_p, &b_p, learning_rate);
		}

		//Print accuracy and cost on test data set, test set should be separated, but I am lazy :/
        X_test = submatrix(X_all);
        Y_test = submatrix(Y_all);
		O = predict(&m_p, &f_p, X_test);

		cout << "Cost for epoch " << i << " is " << mean_cross_entropy_loss(Y_test, O) << endl;
		cout << "Accuracy for epoch " << i << " is " << accuracy(Y_test, O) << endl << endl;
	}

	write_model(&m_p, "model_1.txt");

    return 0;
}
