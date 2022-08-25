#pragma once

//t-SNE algorithm packs multidimensional vectors into 2D or 3D space, trying to keep original metrics.
//Usage:
//    Include header #include "xc_tsne.h"
//    Use class xc_ml::tsne
//Xclu uses original Laurens van der Maaten (Delft University of Technology) implementation:
//    https://github.com/lvdmaaten/bhtsne/
//together with adoptation of Gene Kogan’s code for openFrameworks addon:
//    https://github.com/genekogan/ofxTSNE
//
//t-SNE user guide: https://lvdmaaten.github.io/tsne/User_guide.pdf

#include "incl_h.h"
#include "tsne.h"

//---------------------------------------------------------------------
namespace xc_ml {
//---------------------------------------------------------------------

//CPU t-SNE implementation
//TODO: there is CUDA t-SNE implementation.

class xTSNE
{
public:
    //Parameters:
    //- perplexity (https://medium.com/swlh/t-sne-explained-math-and-intuition-94599ab164cf)
    //    the standard deviation the Gaussian representing the conditional distribution
    //    in the high-dimensional space.
    //    It can be interpreted as the number of effective neighbors for each point.
    //    The model is rather robust for perplexities between 5 to 50.
    //- theta (https://lvdmaaten.github.io/tsne/User_guide.pdf)
    //    specified how coarse the Barnes-Hut approximation is,
    //    setting theta to 0 runs the original O(N2) t-SNE algorithm,
    //    whereas using higher values runs the O(N log N) with increasingly better constant.
    //    The value of theta should be between 0 and 1, and its default value is 0.5.
    //- normalize - should we put resulted vectors to [0,1] square.
    //- runManually - it true, call "iterate" manually to see how process converges.

    struct Params {
        int iterations = 1000;
        double perplexity=30;
        double theta=0.5;
        bool normalize=true;
        bool runManually=false;
    };

    //2D embedding
    QVector<vec2> run_2d(const QVector<QVector<float>> &data, const Params &params);
    QVector<vec2> result_2d();

    //3D embedding
    QVector<vec3> run_3d(const QVector<QVector<float>> &data, const Params &params);
    QVector<vec3> result_3d();

    //Universal callers for other dimensions
    const QVector<QVector<double>> &run(const QVector<QVector<float>> &data, const Params &params, int dims=2);
    const QVector<QVector<double>> &iterate();    
    QVector<QVector<double>> &result();

private:
    void finish();
    
    TSNE tsne;
    QVector<QVector<double>> tsnePoints;
    
    int dims = 0;
    Params params_;
    
    int N, D;
    QVector<double> X, Y;

    int iter = 0;
};

//---------------------------------------------------------------------
} //namespace xc_ml
//---------------------------------------------------------------------
