#include "agent.h"

#include <iostream>

using std::cerr;
using std::cout;
using std::string;

namespace neotitanicml {

bool Agent::Init() {
    if (train_dataset_path_.size()) {
        train_dataset_ = new CMemoryProblem();
        if (!LoadDataset(train_dataset_, train_dataset_path_)) {
            cerr << "Can't load train dataset"
                 << "\n";
            return false;
        }
    }
    if (test_dataset_path_.size()) {
        test_dataset_ = new CMemoryProblem();
        if (!LoadDataset(test_dataset_, test_dataset_path_)) {
            cerr << "Can't load test dataset"
                 << "\n";
            return false;
        }
    }

    return true;
}

bool Agent::SaveModel() {
    try {
        CArchiveFile archive_file(model_path_.c_str(), CArchive::store);
        CArchive archive(&archive_file, CArchive::SD_Storing);

        CString modelName = GetModelName(model_);
        archive << modelName;
        model_->Serialize(archive);

        archive.Close();
        archive_file.Close();
    } catch (std::exception& e) {
        cerr << "Error during save model: " << e.what() << "\n";
        return false;
    }
    return true;
}

bool Agent::LoadModel() {
    try {
        CArchiveFile archive_file(model_path_.c_str(), CArchive::load);
        CArchive archive(&archive_file, CArchive::SD_Loading);

        CString name;
        archive >> name;

        model_ = CreateModel<IModel>(name);
        model_->Serialize(archive);

        archive.Close();
        archive_file.Close();
    } catch (std::exception& e) {
        cerr << "Error during load model: " << e.what() << "\n";
        return false;
    }
    return true;
}

void Agent::Train() {
    // параметры взяты из sklearn
    CSvm::CParams params(CSvmKernel::KT_RBF);
    params.Tolerance = 0.001;
    params.Gamma = 1.0 / 7;

    CSvm svm(params);

    model_ = svm.Train(*train_dataset_);

    float train_score = Validate(train_dataset_);
    float test_score = Validate(test_dataset_);

    cout << "Train accuracy: " << train_score * 100 << "\n";
    cout << "Test accuracy: " << test_score * 100 << "\n";
}

float Agent::Validate() {
    return Validate(test_dataset_);
}

float Agent::Validate(CPtr<CMemoryProblem> dataset) {
    int correct = 0;
    for (int i = 0; i < dataset->GetVectorCount(); i++) {
        CClassificationResult result;
        model_->Classify(dataset->GetVector(i), result);

        if (result.PreferredClass == dataset->GetClass(i)) {
            correct++;
        }
    }

    float accuracy = static_cast<float>(correct) / dataset->GetVectorCount();
    return accuracy;
}

bool Agent::LoadDataset(CPtr<CMemoryProblem> dataset, const string& path) {
    try {
        CArchiveFile archive_file(path.c_str(), CArchive::load);
        CArchive archive(&archive_file, CArchive::SD_Loading);

        dataset->Serialize(archive);

        archive.Close();
        archive_file.Close();
    } catch (std::exception& e) {
        cerr << "Error during load dataset: " << e.what() << "\n";
        return false;
    }
    return true;
}

}  // namespace neotitanicml