package com.topcoder;

import java.io.RandomAccessFile;
import java.io.IOException;
import java.io.EOFException;
import java.util.Scanner;

public class TCReader {
    private RandomAccessFile file;    

    private boolean isSpace(int c) {
        return c == ',' || c == '{' || c == '}' || c == ' ' ||
               c == '"' || c == '\t' || c == '\r' || c == '\n';
    }

    private void verify() throws IOException {
        if(file == null)
            throw new IOException("No file has been connected yet.\n" +
                    "Please call TCReader.connect() to open a file.");
    }    

    public TCReader() {        
        file = null;
    }

    public TCReader(String inputName) throws IOException {
        this.connect(inputName);
    }

    protected void finalize() throws IOException, Throwable {        
        super.finalize();
        this.disconnect();
    }

    public final void connect(String fileName) throws IOException {
        if(file != null)
            throw new IOException("File has already been opened");
        file = new RandomAccessFile(fileName, "rw");                
    }

    public final void disconnect() throws IOException {
        if(file != null) {
            file.close();
            file = null;
        }
    }

    public final void reconnect(String newFileName) throws IOException {
        this.disconnect();
        if(file == null)
            this.connect(newFileName);
    }

    public final char readChar() throws IOException {        
        verify();
        int c;
        if((c = file.read()) == (int)-1)
            throw new IOException("Reached the end of file");
        return (char)c;
    }

    public final String readToken() throws IOException {
        verify();
        StringBuilder ans = new StringBuilder();
        char c;
        while(isSpace(c = readChar()) && c != '"')
            ;
        try {
            if(c == '"') {
                while((c = readChar()) != '"')
                    ans.append(c);
            } else {
                ans.append(c);
                while(!isSpace(c = readChar()))
                    ans.append(c);
            }
        } catch(IOException e) { 
            // skip this exception
        }
        return ans.toString();
    }
    
    public final void skipToken() throws IOException {
        this.readToken();
    }
    
    public final void skipLine() throws IOException {
        verify();
        while(readChar() != '\n')
            ;
    }
    
    public final void skipArray() throws IOException {
        verify();
        while(readChar() != '}')
            ;
    }

    public final int readInt() throws IOException {
        Scanner sc = new Scanner(this.readToken());        
        int ans = sc.nextInt();
        sc.close();
        return ans;
    }
    
    public final long readLong() throws IOException {
        Scanner sc = new Scanner(this.readToken());        
        long ans = sc.nextLong();
        sc.close();
        return ans;
    }
    
    public final boolean readBool() throws IOException {
        Scanner sc = new Scanner(this.readToken()); 
        boolean ans = sc.nextBoolean();
        sc.close();
        return ans;
    }
    
    public final byte readByte() throws IOException {
        Scanner sc = new Scanner(this.readToken());        
        byte ans = sc.nextByte();
        sc.close();
        return ans;
    }
    
    public final double readDouble() throws IOException {
        Scanner sc = new Scanner(this.readToken());
        double ans = sc.nextDouble();
        sc.close();
        return ans;
    }
    
    public final float readFloat() throws IOException {
        Scanner sc = new Scanner(this.readToken());
        float ans = sc.nextFloat();
        sc.close();
        return ans;
    }
    
    public final short readShort() throws IOException {
        Scanner sc = new Scanner(this.readToken());
        short ans = sc.nextShort();
        sc.close();
        return ans;
    }
    
    public final String readString() throws IOException {
        verify();
        StringBuilder ans = new StringBuilder();
        char c;
        while(isSpace(c = readChar()) && c != '"')
            ;
        try {
            while((c = readChar()) != '"')
                ans.append(c);
        } catch(IOException e) { 
            // skip this exception
        }
        return ans.toString();
    }
    
    public final String readLine() throws IOException {
        verify();
        String ans = file.readLine();
        if(ans == null)
            throw new EOFException("Reached the end of file");
        return ans;
    }
    
    public final int[] readIntArray() throws IOException {
        verify();
        char c;
        while((c = readChar()) != '{')
            ;
        int[] ans = new int[1];
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    int tmp[] = new int[maxLen];
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readInt();
            }
        }
        
        if(maxLen > len) {
            int tmp[] = new int[len];
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
    public final long[] readLongArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        long[] ans = new long[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    long tmp[] = new long[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readLong(); //
            }
        }
        
        if(maxLen > len) {
            long tmp[] = new long[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
    public final boolean[] readBoolArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        boolean[] ans = new boolean[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    boolean tmp[] = new boolean[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readBool(); //
            }
        }
        
        if(maxLen > len) {
            boolean tmp[] = new boolean[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
    public final byte[] readByteArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        byte[] ans = new byte[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    byte tmp[] = new byte[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readByte(); //
            }
        }
        
        if(maxLen > len) {
            byte tmp[] = new byte[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
    public final double[] readDoubleArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        double[] ans = new double[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    double tmp[] = new double[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readDouble(); //
            }
        }
        
        if(maxLen > len) {
            double tmp[] = new double[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
    public final float[] readFloatArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        float[] ans = new float[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    float tmp[] = new float[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readFloat(); //
            }
        }
        
        if(maxLen > len) {
            float tmp[] = new float[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }

    public final short[] readShortArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        short[] ans = new short[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar()))
                if(c == '}') {
                    stop = true;
                    break;
                }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    short tmp[] = new short[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readShort(); //
            }
        }
        
        if(maxLen > len) {
            short tmp[] = new short[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }

    public final String[] readStringArray() throws IOException { //
        verify();
        char c;
        while((c = readChar()) != '{')
            ; 
        String[] ans = new String[1]; //
        int len = 0, maxLen = 1;
        for(boolean stop = false; !stop ; ) {
            while(isSpace(c = readChar())) {
                if(c == '}') {
                    stop = true;
                    break;
                }
                if(c == '"')
                    break;
            }
            if(!stop) {
                if(len >= maxLen) {
                    maxLen <<= 1;
                    String tmp[] = new String[maxLen]; //
                    System.arraycopy(ans, 0, tmp, 0, len);
                    ans = tmp; // point to
                    System.gc();
                }
                file.seek(file.getFilePointer() - 1);
                ans[len++] = readString(); //
            }
        }
        
        if(maxLen > len) {
            String tmp[] = new String[len]; //
            System.arraycopy(ans, 0, tmp, 0, len);
            ans = tmp; // point to
            System.gc();
        }
        return ans;
    }
    
}









