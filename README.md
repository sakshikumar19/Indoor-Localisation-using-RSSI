# Localisation of Receiver Using RSSI of LoRa Signals

**CSO 332 Project**

---

## 1. Overview

Indoor navigation is tricky because GPS signals fade once you step inside a building. This project builds an **indoor localization system** that uses **LoRa-based Received Signal Strength Indicator (RSSI)** values to predict which **partition** the receiver is currently located in.

In simple terms: we placed four LoRa transmitters at the corners of a lab, collected their signal strengths across different partitions and trained machine learning models to estimate the receiver’s location.

---

## 2. Hardware & Setup

- **Transmitter Modules:** 4 LoRa nodes (TX_04, TX_74, TX_03, TX_76; where each ID represents a unique transmitter)
- **Receiver:** LilyGO ESP32 LoRa32 module
- **Power Supply:** USB or portable battery
- **Programming Environment:** Arduino IDE for hardware, Python for data analysis and ML

### Data Collection Procedure

1. The lab was divided into four partitions.

2. The receiver was placed 45 cm above the floor, while the four LoRa transmitters were mounted uniformly at the corners of the lab, each positioned 225 cm above the floor.

3. The receiver was moved to different points within each partition.

4. At every point, RSSI values from all four transmitters were recorded.

5. Each reading was stored as a row in CSV format:

   ```
   X, Y, TX_04, TX_74, TX_03, TX_76, Partition
   ```

6. **350 samples** were collected (≈ 80–90 per partition).

**Transmitter Parameters:**

| Parameter        | Value   |
| ---------------- | ------- |
| Frequency        | 868 MHz |
| Spreading Factor | 7       |
| Bandwidth        | 125 kHz |
| Transmit Power   | +14 dBm |

---

## 3. Dataset

- **Total Samples:** 350
- **Features:** RSSI values (in dBm) from 4 transmitters
- **Target:** Partition label (1–4)

---

## 4. Methodology

### Step 1: Feature Engineering

To make the model more spatially aware, we generated derived features such as:

- Differences between RSSI values, giving gradient of signal strength.
- Aggregate statistics like mean, standard deviation and range, to capture overall signal conditions.
- Ratios between RSSI values, signalling dominance indicators (which transmitter is strongest)

### Step 2: Model Training

The following algorithms were trained and compared:

- K-Nearest Neighbors (KNN)
- Random Forest
- Gradient Boosting
- Support Vector Machine (SVM)
- Neural Network
- Ensemble (Voting Classifier)

Each model was tuned using **GridSearchCV** for hyperparameter optimization.

### Step 3: Evaluation

| Model                 | Test Accuracy |
| --------------------- | ------------- |
| **Ensemble**          | 75.71%        |
| **KNN**               | 74.29%        |
| **Gradient Boosting** | 73.71%        |
| **Random Forest**     | 72.86%        |
| **Neural Network**    | 71.43%        |
| **SVM**               | 71.14%        |

Average accuracy ranged between **70–75%**, depending on signal stability and feature set.

---

## 5. Usage

### Install Requirements

```bash
pip install -r requirements.txt
```

### Run the Notebook

Running the Jupyter notebook will:

1. Load and preprocess the dataset
2. Perform feature engineering
3. Train and evaluate ML models
4. Display accuracy metrics and confusion matrices
5. Recommend the best-performing model

---

## 6. Key Observations

- **Signal dominance patterns** were strong indicators of partition.
- **Feature engineering** improved accuracy compared to raw RSSI input.
- **Ensemble methods** balanced accuracy and stability.
- **System is lightweight** and can be extended for real-time localization.

---

## 7. Scalability

| Environment  | Transmitters | Partitions | Expected Accuracy |
| ------------ | ------------ | ---------- | ----------------- |
| Small Lab    | 4            | 4          | 70–75%            |
| Hostel       | 6            | 9          | 65–70%            |
| Office Space | 8–10         | 16         | 60–65%            |

Try to collect at least 50–100 labeled samples per partition for stable results.

---

## 8. Conclusion

This project demonstrates an approach to indoor localization using LoRa and machine learning. While the accuracy can vary with noise and obstacles, results show that combining **RSSI-based features** with **ensemble learning** gives us a good baseline for indoor positioning.
