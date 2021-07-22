#include "xc_tsne.h"
#include "incl_cpp.h"

namespace xc_ml {

//---------------------------------------------------------------------
//2D embedding
QVector<glm::vec2> xTSNE::run_2d(QVector<QVector<float>> &data, const Params &params) {
    int dim = 2;
    auto &v = run(data, params, dim);
    int n = v.size();
    if (n > 0 && v[0].size() != dim) {
        xc_exception("xTSNE::run_2d internal error - bad resulted vectors size");
    }
    QVector<glm::vec2> res(n);
    for (int i=0; i<n; i++) {
        res[i] = glm::vec2(v[i][0], v[i][1]);
    }
    return res;
}

//---------------------------------------------------------------------
//3D embedding
QVector<glm::vec3> xTSNE::run_3d(QVector<QVector<float>> &data, const Params &params) {
    int dim = 3;
    auto &v = run(data, params, dim);
    int n = v.size();
    if (n > 0 && v[0].size() != dim) {
        xc_exception("xTSNE::run_3d internal error - bad resulted vectors size");
    }
    QVector<glm::vec3> res(n);
    for (int i=0; i<n; i++) {
        res[i] = glm::vec3(v[i][0], v[i][1], v[i][2]);
    }
    return res;
}

//---------------------------------------------------------------------
const QVector<QVector<double>> &xTSNE::run(QVector<QVector<float>> &data, const Params &params, int dims) {
    params_ = params;
    this->dims = dims;
    
    iter = 0;

    //number of input vectors
    xc_assert(data.size() > 0, "xTSNE::run() - provided empty data set");
    N = data.size();
    //input dimensions, check coherence
    D = data[0].size();
    for (int i=1; i<N; i++) {
        xc_assert(data[i].size() == D, "xTSNE::run() - all input vectors must have the same size");
    }

    //check perplexity validity
    if (N - 1 < 3 * params_.perplexity) {
        //ofLog(OF_LOG_WARNING, "Perplexity too large for number of data points, setting to max");
        params_.perplexity = (float) (N-1) / 3.0 - 1.0;
    }
    
    X.resize(D * N);
    Y.resize(dims * N);
    
    int idx = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<D; j++) {
            X[idx] = data[i][j];
            idx++;
        }
    }

    // t-SNE
    tsne.run(X.data(), N, D, Y.data(), dims, params_.perplexity, params_.theta, params_.runManually);
    
    if (params_.runManually) {
        return tsnePoints;
    }
    return iterate();
}

//---------------------------------------------------------------------
const QVector<QVector<double>> &xTSNE::iterate(){
    if (iter > params_.iterations) {
        return tsnePoints;
    }
    
    if (params_.runManually) {
        tsne.runIteration();
    }
    
    // keep track of min for normalization
    QVector<double> min_, max_;
    min_.resize(dims);
    max_.resize(dims);
    for (int i=0; i<dims; i++) {
        min_[i] = std::numeric_limits<double>::max();
        max_[i] = std::numeric_limits<double>::min();
    }
    
    // unpack Y into tsnePoints
    tsnePoints.resize(N);
    int idxY = 0;
    for (int i=0; i<N; i++) {
        QVector<double> &tsnePoint = tsnePoints[i];
        tsnePoint.resize(dims);
        for (int j=0; j<dims; j++) {
            tsnePoint[j] = Y[idxY];
            if (params_.normalize) {
                if (tsnePoint[j] < min_[j])  min_[j] = tsnePoint[j];
                if (tsnePoint[j] > max_[j])  max_[j] = tsnePoint[j];
            }
            idxY++;
        }
    }
    
    // normalize if requested
    if (params_.normalize) {
        for (int i=0; i<tsnePoints.size(); i++) {
            for (int j=0; j<dims; j++) {
                tsnePoints[i][j] = (tsnePoints[i][j] - min_[j]) / (max_[j] - min_[j]);
            }
        }
    }
    
    iter++;
    if (iter == params_.iterations) {
        finish();
    }
    
    return tsnePoints;
}

//---------------------------------------------------------------------
void xTSNE::finish() {
    //Following the help on QVector::clear(), from Qt 5.7, the capacity of QVector is preserved.
    //So need use 'swap' to clear it
    QVector<double>().swap(X);
    QVector<double>().swap(Y);
}

//---------------------------------------------------------------------
} //namespace xc_ml
//---------------------------------------------------------------------
