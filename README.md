# Indoor Localization System

### CSO 332 Project

A machine learning-based indoor localization system using RSSI (Received Signal Strength Indicator) values from multiple transmitters to predict location partitions.

---

## Problem Statement

GPS doesn't work indoors. We solve this by placing 4 Bluetooth transmitters in corners of a lab and using their signal strengths to determine which partition (zone) a device is in.

---

## Dataset

- **350 data points** collected across a lab divided into 4 partitions
- **4 transmitters**: TX_04, TX_74, TX_03, TX_76 (placed in corners)
- **Features**: RSSI values (in dBm) from each transmitter
- **Target**: Partition number (1-4)

---

## Methodology

### 1. Feature Engineering

Created derived features that capture spatial patterns:

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

All models optimized using GridSearchCV hyperparameter tuning.

### 3. Best Results

- **Accuracy**: 70-75% (varies by model)
- **Best Features**: Signal ratios and differences outperform raw RSSI
- **Fastest Model**: Ensemble

---

## Usage

### Prerequisites

```bash
pip install -r requirements.txt
```

### Run Analysis

Run the cells one-by-one or all at once.

The script will:

1. Perform exploratory data analysis
2. Engineer features and analyze patterns
3. Train and optimize multiple ML models
4. Compare performance and recommend best model
5. Provide scaling strategies for larger spaces

---

## Key Insights

**Signal dominance patterns** are key - each partition is closest to a different transmitter  
**Feature engineering** significantly improves accuracy over raw RSSI  
**Ensemble methods** provide best accuracy with minimal overfitting  
**Model is lightweight** - suitable for real-time mobile deployment

---

## Scaling to Larger Spaces

| Space Size | Transmitters | Partitions | Expected Accuracy |
| ---------- | ------------ | ---------- | ----------------- |
| Small lab  | 4            | 4          | 70-75%            |
| Office     | 6            | 9          | 65-70%            |
| Warehouse  | 8-10         | 16         | 60-65%            |

**Rule of thumb**: ~1 transmitter per 100m², 50-100 samples per partition

---
