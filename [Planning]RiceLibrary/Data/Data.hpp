#pragma once

struct Util
{
    template <typename T, int N>
    struct vec
    {
        T items[N];

        T& operator[](int index) { return items[index]; }
        const T& operator[](int index) const { return items[index]; }

        vec operator+(const vec& other) const
        {
        vec res;
        for (int i = 0; i < N; ++i) res.items[i] = this->items[i] + other.items[i];
        return res;
        }

        vec operator-(const vec& other) const
        {
        vec res;
        for (int i = 0; i < N; ++i) res.items[i] = this->items[i] - other.items[i];
        return res;
        }

        float operator*(const vec& other) const
        {
            float res;
            for (int i = 0; i < N; ++i) res += this->items[i]*other.items[i]
            return res;
        }
        vec operator*(const float& scale) const
        {
            vec res;
            for (int i = 0; i < N; ++i) res.item[i] = this->items[i]*scale;
            return res;
        }
        vec operator%(const vec& other) const
        {
            static_assert(N == 3, "input a vec3");
            vec res;

            for (int i = 0; i < 3; ++i)
            {
            int j = (i + 1) % 3;
            int k = (i + 2) % 3;
            res.items[i] = (this->items[j] * other.items[k]) - (this->items[k] * other.items[j]);
            }

            return res;
        }
        float length() const
        {
            return std::sqrt(this*(*this));
        }
        float distance(const vec& other) const
        {
            return length(this-other);
        }
        vec normalize() const
        {
            return this*(1/length(this));
        }
    };

    template <typename T, int W, int L>
    struct Matrix
    {
        T items[W*L];
        T& operator()(int x , int y) { return items[x+y*W]; }
        const T& operator()(int x, int y) const { return items[x+y*W]; }
        //+-/*
        //inverse
        //translate
        //scale
        //convert
    };

    struct quaternion
    {
        vec<float, 3> v = {0, 0, 0};
        float w = 1.0;
        vec<float, 3> operator()(const vec<float, 3>& p) const
        {
            vec<float, 3> uv = v % p;
            vec<float, 3> uuv = v % uv;
            return p + (uv * (2.0f * w)) + (uuv * 2.0f);
        }
        void set(const vec<float, 3>& nv, const float nw)
        {
            v = nv;
            w = nw;
        }
        //+-*/
        //inverse
        //normalize
        //convert
    };

    struct calendar
        {
        int y, m, wk, d, hr, min, s, ms;
        vec<int, 8> get() const {return vec<int, 8>{y, m, wk, d, hr, min, s, ms};}
        void set(int zone)
            {
                std::time_t t = std::time(nullptr) + (zone * 3600);
                std::tm* utc = std::gmtime(&t);

                y   = utc->tm_year + 1900;
                mon = utc->tm_mon + 1;
                w   = utc->tm_wday;
                d   = utc->tm_mday;
                h   = utc->tm_hour;
                min = utc->tm_min;
                s   = utc->tm_sec;
                ms  = 0;
            }
        };

    class Clock
        {
        private:
            std::chrono::steady_clock::time_point PrevFrame;
            float accum;
            float step;
            float Dt;

        public:

            Clock() : accum(0.0f), step(1.0f / 144.0f), Dt(0.0f), PrevFrame(std::chrono::steady_clock::now()) {}

            struct Stopwatch
            {
                std::chrono::steady_clock::time_point Start;
                float Limit;
                Stopwatch(float seconds) : Start(std::chrono::steady_clock::now()), Limit(seconds) {}
                bool IsExpired() const
                {
                    auto current_time = std::chrono::steady_clock::now();
                    std::chrono::duration<float> elapsed = current_time - Start;
                    return elapsed.count() >= Limit;
                }
            };

            void Clock::Update()
            {
                auto currentFrame = std::chrono::steady_clock::now();
                std::chrono::duration<float> elapsed = currentFrame - PrevFrame;
                PrevFrame = currentFrame;

                Dt = elapsed.count();
                accum += Dt;
            }

            bool Clock::FixedUpdate()
            {
                if (accum >= step)
                {
                    accum -= step;
                    return true;
                }
                return false;
            }
            const float& GetDt() { return Dt; }
            const float& GetStep() { return step; }
        };

    template<>template <int L>
    struct ChunkPoints
    {
    int size = L*L*L;
    bool items[size] = {false};

    bool operator()(int ID) const
    {
        return items[ID];
    }

    bool& operator()(int ID)
    {
        return items[ID];
    }

    bool operator()(int x, int y, int z) const
    {
        return items[x + L * (y + L * z)];
    }

    bool& operator()(int x, int y, int z)
    {
        return items[x + L * (y + L * z)];
    }
    int pack()
    {
        int res = 0;
        for (int i = 0; i < size; i++)
        {
            if (items[i])
            {
            res |= (1 << i);
            }
        }
            return res;
    }

    void unpack(int packed)
    {
       for (int i = 0; i < size; i++)
         {
            items[i] = (packed >> i) & 1;
         }
    }
    };

    struct ray
    {
        vec<float, 3> anchor = {0,0,0};
        vec<float, 3> dir = {0,0,1};
        vec<float, 3> point(const float& dist) const {return anchor + dir*dist;};
        void set(const vec<float, 3>& na, const vec<float,3> nd)
        {
            anchor = na;
            dir = nd;
        }
        //intersect
    };


    struct triangle
    {
        vec<vec<float, 3>, 3> tris = {{0,0,0}{0,0,0}{0,0,0}};
        const& vec<float, 3> operator()(int point) const
        {
            return this->points[point];
        }
        const& vec<float, 3> centroid() const
        {
            return (points[0] + points[1] + points[2])*(1/3);
        }
        const& vec<float, 3> normal() const
        {
            return (point[1] - point[0]) % (point[2] - point[0]);
        }
        //convert
        //intersecting
    };
};

struct IO
{
    void method1();
    void method2();
};

struct Memory {
    void method1();
    void method2();
};

struct exData{
    Utility util;
    IO io;
    Memory mem;
};

extern exData data;