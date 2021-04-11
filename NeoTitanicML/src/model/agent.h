#ifndef NEOTITANICML_MODEL_AGENT_H_
#define NEOTITANICML_MODEL_AGENT_H_

#include <NeoML/NeoML.h>

#include "common.h"

namespace neotitanicml {

class Agent {
 public:
    /// Конструкто
    Agent() {}

    /**
     * Конструктор для проверки модели на датасете
     * 
     * @param model_path Путь до сохранённой модели
     * @param test_dataset_path Датасет для теста
     */
    Agent(const std::string& model_path,
          const std::string& test_dataset_path) : model_path_(model_path),
                                                  test_dataset_path_(test_dataset_path) {}

    /**
     * Конструкто для обучения модели
     * 
     * @param model_path Путь, где сохранить модель
     * @param train_dataset_path Датасет для обучения
     * @param test_dataset_path датасет для теста
     */
    Agent(const std::string& model_path,
          const std::string& train_dataset_path,
          const std::string& test_dataset_path) : model_path_(model_path),
                                                  train_dataset_path_(train_dataset_path),
                                                  test_dataset_path_(test_dataset_path) {}

    /**
     * Инициализация агента
     * 
     * @return В случае успеха true
     */
    bool Init();

    /**
     * Загрузка модели из файла
     * 
     * @return В случае успеха true 
     */
    bool LoadModel();

    /**
     * Сохранене модели в файл
     * 
     * @return В случае успеха true 
     */
    bool SaveModel();

    /**
     * Обучение модели на представлнных данных
     */
    void Train();

    /**
     * Валидация модели на тестовых данных.
     * 
     * @return Значение выбранной меры качества (по-умолчанию accuracy)
     */
    float Validate();

    /**
     * Валидация на указанном датасете
     * 
     * @return Значение выбранной меры качества (по-умолчанию accuracy)
     */
    float Validate(CPtr<CMemoryProblem> dataset);

 private:
    // Загрузить датасет из файла
    bool LoadDataset(CPtr<CMemoryProblem> dataset, const std::string& path);

    CPtr<IModel> model_;

    CPtr<CMemoryProblem> train_dataset_;
    CPtr<CMemoryProblem> test_dataset_;

    std::string model_path_;
    std::string train_dataset_path_;
    std::string test_dataset_path_;
};

}  // namespace neotitanicml

#endif  // NEOTITANICML_MODEL_AGENT_H_