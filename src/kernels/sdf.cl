class Sdf {
    public:
        virtual inline float dist(float3 p) const = 0;

        virtual inline float operation()(float3 p) const {
            return this->dist(p);
        }
};
