#ifndef COORDS_H
#define COORDS_H


class coords
{
    public:
        coords();
        coords(int x, int y);
        virtual ~coords();
        int get_abs();
        int get_ord();
        void set_coords(int x, int y);
        bool is_equal(coords *other);

    private:
        int x;
        int y;
};

#endif // COORDS_H
