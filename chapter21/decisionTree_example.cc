//Example 21-1. Creating and training a decision tree

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace cv;

void help(char **argv) {
  cout << "\n\n"
       << "Using binary decision trees to learn to recognize poisonous\n"
       << "    from edible mushrooms based on visible attributes.\n"
       << "    This program demonstrates how to create and a train a \n"
       << "    decision tree using ml library in OpenCV.\n"
       << "Call:\n" << argv[0] << " <csv-file-path>\n\n"
       << "\nIf you don't enter a file, it defaults to ../resource/21/mushroom/agaricus-lepiota.data\n"
       << endl;
}

int main(int argc, char *argv[]) {
  // If the caller gave a filename, great. Otherwise, use a default.
  //
  const char *csv_file_name = argc >= 2 ? argv[1] : "../resource/21/mushroom/agaricus-lepiota.data";
  cout << "OpenCV Version: " << CV_VERSION << endl;
  help(argv);

  // Read in the CSV file that we were given.
  //
  cv::Ptr<cv::ml::TrainData> data_set =
      cv::ml::TrainData::loadFromCSV(csv_file_name, // Input file name
                                     0, // Header lines (ignore this many)
                                     0, // Responses are (start) at thie column
                                     1, // Inputs start at this column
                                     "cat[0-22]" // All 23 columns are categorical
                                     );
  // Use defaults for delimeter (',') and missch ('?')
  // Verify that we read in what we think.
  //
  int n_samples = data_set->getNSamples();
  if (n_samples == 0) {
    cerr << "Could not read file: " << csv_file_name << endl;
    exit(-1);
  } else {
    cout << "Read " << n_samples << " samples from " << csv_file_name << endl;
  }

  // Split the data, so that 90% is train data
  //
  data_set->setTrainTestSplitRatio(0.90, false);
  int n_train_samples = data_set->getNTrainSamples();
  int n_test_samples = data_set->getNTestSamples();
  cout << "Found " << n_train_samples << " Train Samples, and "
       << n_test_samples << " Test Samples" << endl;

  cout << "Vars:" << data_set->getNVars()<<endl;
  cout << "All Vars:" << data_set->getNAllVars()<<endl;
  std::vector<cv::String> names;
  data_set->getNames(names);
  cout << "Names: ";
  for(auto it = names.begin(); it != names.end(); ++it)
  {
      cout << *it << "  ";
  }
  cout << endl;

  // Create a DTrees classifier.
  //
  cv::Ptr<cv::ml::RTrees> dtree = cv::ml::RTrees::create();
  // set parameters
  //
  // These are the parameters from the old mushrooms.cpp code
  // Set up priors to penalize "poisonous" 10x as much as "edible"
  //
  float _priors[] = {1.0, 10.0};
  cv::Mat priors(1, 2, CV_32F, _priors);
  dtree->setMaxDepth(8);
  dtree->setMinSampleCount(10);
  dtree->setRegressionAccuracy(0.01f);
  dtree->setUseSurrogates(false /* true */);
  dtree->setMaxCategories(15);
  dtree->setCVFolds(0 /*10*/); // nonzero causes core dump
  dtree->setUse1SERule(true);
  dtree->setTruncatePrunedTree(true);
  dtree->setPriors( priors );
  //dtree->setPriors(cv::Mat()); // ignore priors for now...
  // Now train the model
  // NB: we are only using the "train" part of the data set
  //
  dtree->train(data_set);

  // Having successfully trained the data, we should be able
  // to calculate the error on both the training data, as well
  // as the test data that we held out.
  //
  cv::Mat results;
  float train_performance = dtree->calcError(data_set,
                                             false, // use train data
                                             results // cv::noArray()
                                             );

  //Mat flags = data_set->getVarSymbolFlags();

  // Compute some statistics on our own:
  //
  {
    cv::Mat expected_responses = data_set->getResponses();
    int good = 0, bad = 0, total = 0;
    for (int i = 0; i < data_set->getNTrainSamples(); ++i) {
      float received = results.at<float>(i, 0);
      float expected = expected_responses.at<float>(i, 0);
      cv::String r_str = names[(int)received];
      cv::String e_str = names[(int)expected];
      //cout << "Expected: " << e_str << ", got: " << r_str << endl;
      if (received == expected)
        good++;
      else
        bad++;
      total++;
    }
    cout << "Correct answers: " <<(float(good)/total) <<" % " << endl;
                cout << "Incorrect answers: " << (float(bad) / total) << "%"
         << endl;
  }
  float test_performance = dtree->calcError(data_set,
                                            true, // use test data
                                            results // cv::noArray()
                                            );
  cout << "Performance on training data: " << train_performance << "%" << endl;
  cout << "Performance on test data: " <<test_performance <<" % " <<endl;

  // To save your trained classifier to disk:
  //
  dtree->save("decisionTree.xml");

  dtree->clear();

  // To load a trained classifier from disk:
  dtree->load<cv::ml::RTrees>("decisionTree.xml");

 //cout <<  data_set->getSamples();
  //cv::Mat mushroom_sample = (cv::Mat_<float>(1, 23) << 1, 8, 13, 4, 6, 18, 14, 7, 15, 10, 9, 7, 8, 13, 7, 7, 1, 10, 4, 4, 10, 7, 20);
  cv::Mat mushroom_sample(1, names.size()-1, CV_32FC1);
  string mushroom = "xsntpfcnkeessw?pwopksu";
  int mushroom_index = 0;
  for(auto it = mushroom.begin(); it != mushroom.end(); ++it)
  {
    for(int i = 0; i < names.size(); i++)
    {
      if(names[i][0] == *it)
      {
          mushroom_sample.at<float>(0, mushroom_index) = i;
      }
    }
    mushroom_index++;
  }

  cout <<"musshroom sample:" <<mushroom_sample <<endl;

  // return index e: 9  p: 1
  float result = dtree->predict(mushroom_sample);
  cout << "result: " << result << endl;
  return 0;
}