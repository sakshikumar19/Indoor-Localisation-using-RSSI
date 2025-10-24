# Indoor Localization System

### CSO 332 Project

A machine learning-based indoor localization system using RSSI (Received Signal Strength Indicator) values from multiple transmitters to predict location partitions.

---

## Problem Statement

GPS doesn't work indoors. We solve this by placing 4 LoRa transmitters in corners of a lab and using their signal strengths to determine which partition (zone) a device is in.

---

## Hardware Setup & Data Collection

- **Transmitter Modules**: 4 LoRa nodes (TX_04, TX_74, TX_03, TX_76) placed in the corners of the lab.
- **Receiver Module**: LilyGO ESP32 with LoRa module, mobile unit used to collect RSSI signals.
- **Power Supply**: USB or battery packs for transmitters and ESP32.
- **Data Logging**: Receiver connected to a laptop via USB to log RSSI values.

**Data Collection Procedure**:

1. Lab divided into 4 partitions (P1–P4).
2. Receiver placed at multiple positions within each partition.
3. ESP32 recorded RSSI values from all 4 transmitters over time.
4. Each sample saved as:

   ```
   TX_04, TX_74, TX_03, TX_76, Partition
   ```

5. Total samples collected: ~350 (≈ 80–90 per partition).

Below is the floorplan used during data collection:
![Lab Floorplan](images/lab_floorplan.png)

**Transmitter Configuration**:

| Parameter        | Value   |
| ---------------- | ------- |
| Frequency        | 868 MHz |
| Spreading Factor | 7       |
| Bandwidth        | 125 kHz |
| Transmit Power   | +14 dBm |

---

## Dataset

- **350 data points** collected across a lab divided into 4 partitions
- **4 transmitters**: TX_04, TX_74, TX_03, TX_76 (placed in corners)
- **Features**: RSSI values (in dBm) from each transmitter
- **Target**: Partition number (1-4)

---

## Methodology

### 1. Feature Engineering

Derived features that capture spatial patterns:

- Signal ratios between transmitters (dominance patterns)
- Signal differences (which TX is stronger?)
- Statistical aggregates (mean, std, range)

### 2. Models Tested

- Random Forest
- Gradient Boosting
- Support Vector Machine (SVM)
- K-Nearest Neighbors (KNN)
- Neural Network
- Ensemble (Voting Classifier)

_All models optimized using GridSearchCV hyperparameter tuning._

### 3. Results

- **Accuracy**: 70-75% (varies by model)
- **Best Features**: Signal ratios and differences outperform raw RSSI
- **Fastest Model**: Ensemble

| Model                 | Test Accuracy |
| --------------------- | ------------- |
| **Ensemble**          | 75.71%        |
| **KNN**               | 74.29%        |
| **Random Forest**     | 72.86%        |
| **Gradient Boosting** | 72.86%        |
| **SVM**               | 72.86%        |
| **Neural Network**    | 71.43%        |

---

## Usage

### Prerequisites

```bash
pip install -r requirements.txt
```

### Run Analysis

Run the cells one-by-one or all at once. The script will:

1. Perform exploratory data analysis
2. Engineer features and analyze patterns
3. Train and optimize multiple ML models
4. Compare performance and recommend best model
5. Provide scaling strategies for larger spaces

---

## Key Insights

- **Signal dominance patterns** are key - each partition is closest to a different transmitter
- **Feature engineering** significantly improves accuracy over raw RSSI
- **Ensemble methods** provide best accuracy with minimal overfitting
- **Model is lightweight** - suitable for real-time mobile deployment

---

## Scaling to Larger Spaces

| Space Size | Transmitters | Partitions | Expected Accuracy |
| ---------- | ------------ | ---------- | ----------------- |
| Small lab  | 4            | 4          | 70-75%            |
| Office     | 6            | 9          | 65-70%            |
| Warehouse  | 8-10         | 16         | 60-65%            |

**Rule of thumb**: ~1 transmitter per 100m², 50-100 samples per partition
