//
// Created by danila on 29.04.19.
//

#include "algorithms.hpp"

#include <queue>
#include <cmath>

std::vector<double> degree_centrality(const graph& g){
    std::vector<double> res;

    for(auto& it: g.edges){
        res.emplace_back(static_cast<double >(it.size())/(g.edges.size()-1));
    }

    return res;
}

std::vector<double> closness_centrality(const graph& g){
    auto d = get_all_distance(g);

    std::vector<double> res;

    for(auto& line: d){
        double s = 0;
        for(auto &it:line){
            s += it;
        }

        res.emplace_back(static_cast<double >(g.edges.size()-1)/s);
    }

    return res;
}

std::vector<double> betweenness_centrality(const graph& g){
    auto sdist = get_all_distance(g);

    std::vector<std::vector<int>> pred(g.edges.size());
    std::vector<int> din(g.edges.size());
    std::vector<int> in_din(g.edges.size());
    std::queue<int> q;
    std::vector<int> was(g.edges.size());

    std::vector<double> res(g.edges.size(), 0);

    for(size_t s=0;s<g.edges.size();++s){
        for(auto& line:pred){
            line.clear();
        }

        std::fill(din.begin(), din.end(), 0);
        std::fill(was.begin(), was.end(), 0);

        q.push(s);
        din[s] = 1;
        was[s] = 1;

        while(!q.empty()){
            int nv = q.front();
            q.pop();

            for(auto& it: g.edges[nv]){
                if(sdist[s][nv]+1 == sdist[s][it]){
                    din[it] += din[nv];
                    pred[it].emplace_back(nv);
                }
                if(was[it] == 0){
                    was[it] = 1;
                    q.push(it);
                }
            }
        }

        for(size_t t=0; t<g.edges.size(); ++t){
            if(s == t){
                continue;
            }

            std::fill(in_din.begin(), in_din.end(), 0);
            std::fill(was.begin(), was.end(), 0);

            q.push(t);
            in_din[t] = 1;
            was[t] = 1;

            while(!q.empty()){
                int nv = q.front();
                q.pop();

                if(nv == s){
                    continue;
                }

                if(nv != t) {
                    res[nv] += static_cast<double>(in_din[nv]*din[nv])/din[t];
                }

                for(auto& it: pred[nv]){
                    in_din[it] += in_din[nv];
                    if(was[it] == 0){
                        was[it] = 1;
                        q.push(it);
                    }
                }
            }
        }
    }

    for(auto &it:res){
        it *= 1./(g.edges.size()-1)/(g.edges.size()-2);
    }

    return res;
}

std::vector<std::vector<double>> edge_betweenness(const graph &g) {
    auto sdist = get_all_distance(g);

    std::vector<std::vector<double>> res(g.edges.size(),
            std::vector<double>(g.edges.size(), 0));

    std::vector<std::vector<int>> pred(g.edges.size());
    std::vector<int> din(g.edges.size());
    std::vector<int> in_din(g.edges.size());
    std::queue<int> q;
    std::vector<int> was(g.edges.size());

    for(size_t s=0;s<g.edges.size();++s){
        for(auto& line:pred){
            line.clear();
        }

        std::fill(din.begin(), din.end(), 0);
        std::fill(was.begin(), was.end(), 0);

        q.push(s);
        din[s] = 1;
        was[s] = 1;

        while(!q.empty()){
            int nv = q.front();
            q.pop();

            for(auto& it: g.edges[nv]){
                if(sdist[s][nv]+1 == sdist[s][it]){
                    din[it] += din[nv];
                    pred[it].emplace_back(nv);
                }
                if(was[it] == 0){
                    was[it] = 1;
                    q.push(it);
                }
            }
        }

        for(size_t t=0; t<g.edges.size(); ++t){
            if(s == t){
                continue;
            }

            std::fill(in_din.begin(), in_din.end(), 0);
            std::fill(was.begin(), was.end(), 0);

            q.push(t);
            in_din[t] = 1;
            was[t] = 1;

            while(!q.empty()){
                int nv = q.front();
                q.pop();

                for(auto& it: pred[nv]){
                    in_din[it] += in_din[nv];
                    res[it][nv] += static_cast<double>(in_din[nv]*din[it])/din[t];
                    if(was[it] == 0){
                        was[it] = 1;
                        q.push(it);
                    }
                }
            }
        }
    }

    for(auto &line:res){
        for(auto& it:line){
            it *= 2./(g.edges.size()-1)/(g.edges.size());
        }
    }

    return res;
}

void normalise(std::vector<double>& vec){
    double mx = 0;
    for(auto &it:vec){
        mx += it*it;
    }
    mx = std::sqrt(mx);
    if(std::abs(mx) < 1e-4){
        return;
    }

    for(auto &it:vec){
        it /= mx;
    }
}

std::vector<double> mult(const std::vector<std::vector<int>>& A,
        const std::vector<double>& b){
    std::vector<double> res(A.size(), 0);

    for(size_t i=0;i<A.size();++i){
        for(size_t j=0;j<b.size();++j){
            res[i] += A[i][j]*b[j];
        }
    }

    return res;
}

double diff(const std::vector<double>& l, const std::vector<double>& r){
    double res = 0;
    for(size_t i=0;i<l.size();++i){
        res += (l[i] - r[i])*(l[i] - r[i]);
    }
    return std::sqrt(res);
}

std::vector<double> eigenvector_centrality(const graph &g, int iter_num, 
        double eps) {
    std::vector<double> next(g.edges.size(), std::sqrt(1./g.edges.size()));
    std::vector<double> prev(g.edges.size(), 0);

    auto m = g.get_edge_mat();

    for(size_t i=0;i<iter_num && diff(prev, next)> eps;++i){
        prev = next;
        next = mult(m, prev);
        normalise(next);
    }

    return next;
}

