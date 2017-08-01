//
// Source code recreated from a .class file by IntelliJ IDEA
// (powered by Fernflower decompiler)
//

package iburrell.util;

import java.util.Random;

public class RandomScale {
    private Random gen;
    private final int RAND_MAX = 2147483647;

    public RandomScale(long var1) {
        this.gen = new Random(var1);
    }

    public RandomScale() {
        this.gen = new Random();
    }

    public double randomDouble() {
        return this.gen.nextDouble();
    }

    public double randomDouble(double var1) {
        return this.gen.nextDouble() * var1;
    }

    public double randomDouble(double var1, double var3) {
        return this.randomDouble(var3 - var1) + var1;
    }

    public int randomInt() {
        return Math.abs(this.gen.nextInt());
    }

    public int randomInt(int var1) {
        return (int)Math.floor(this.randomDouble((double)var1));
    }

    public int randomInt(int var1, int var2) {
        return this.randomInt(var2 - var1) + var1;
    }
}
