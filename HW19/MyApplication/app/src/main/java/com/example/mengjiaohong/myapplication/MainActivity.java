package com.example.mengjiaohong.myapplication;

// libraries

import android.Manifest;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.SurfaceTexture;
import android.hardware.Camera;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.TextureView;
import android.view.WindowManager;
import android.widget.TextView;
import android.widget.SeekBar;
import android.widget.SeekBar.OnSeekBarChangeListener;

import java.io.IOException;

import static android.graphics.Color.blue;
import static android.graphics.Color.green;
import static android.graphics.Color.red;
import static android.graphics.Color.rgb;

public class MainActivity extends Activity implements TextureView.SurfaceTextureListener {
    private Camera mCamera;
    private TextureView mTextureView;
    private SurfaceView mSurfaceView;
    private SurfaceHolder mSurfaceHolder;
    private Bitmap bmp = Bitmap.createBitmap(640, 480, Bitmap.Config.ARGB_8888);
    private Canvas canvas = new Canvas(bmp);
    private Paint paint1 = new Paint();
    private TextView mTextView;

    static long prevtime = 0; // for FPS calculation
    int thresh = 0, range = 0;
    float COM = 0;
    SeekBar myControl, rangeControl;

    private void setMyControlListener() {
        myControl.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                thresh = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }
    private void setrangeControlListener() {
        rangeControl.setOnSeekBarChangeListener(new OnSeekBarChangeListener() {

            int progressChanged = 0;

            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChanged = progress;
                range = progress;
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); // keeps the screen from turning off

        mTextView = (TextView) findViewById(R.id.cameraStatus);

        myControl = (SeekBar) findViewById(R.id.seek1);
        rangeControl = (SeekBar) findViewById(R.id.seek2);

        setMyControlListener();
        setrangeControlListener();

        // see if the app has permission to use the camera
        ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.CAMERA}, 1);
        if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED) {
            mSurfaceView = (SurfaceView) findViewById(R.id.surfaceview);
            mSurfaceHolder = mSurfaceView.getHolder();

            mTextureView = (TextureView) findViewById(R.id.textureview);
            mTextureView.setSurfaceTextureListener(this);

            // set the paintbrush for writing text on the image
            paint1.setColor(0xffff0000); // red
            paint1.setTextSize(24);

            mTextView.setText("started camera");
        } else {
            mTextView.setText("no camera permissions");
        }

    }

    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        mCamera = Camera.open();
        Camera.Parameters parameters = mCamera.getParameters();
        parameters.setPreviewSize(640, 480);
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_INFINITY); // no autofocusing
        parameters.setAutoExposureLock(true); // keep the white balance constant
        mCamera.setParameters(parameters);
        mCamera.setDisplayOrientation(90); // rotate to portrait mode

        try {
            mCamera.setPreviewTexture(surface);
            mCamera.startPreview();
        } catch (IOException ioe) {
            // Something bad happened
        }
    }

    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
        // Ignored, Camera does all the work for us
    }

    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        mCamera.stopPreview();
        mCamera.release();
        return true;
    }

    public int abs (int n){
        if(n < 0){
            return -n;
        } else{
            return n;
        }
    }

    // the important function
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
        // every time there is a new Camera preview frame
        mTextureView.getBitmap(bmp);

        final Canvas c = mSurfaceHolder.lockCanvas();
        if (c != null) {
            int[] pixels = new int[bmp.getWidth()]; // pixels[] is the RGBA data
            for (int startY = 0; startY < bmp.getHeight(); startY++) {
                bmp.getPixels(pixels, 0, bmp.getWidth(), 0, startY, bmp.getWidth(), 1);

                int sum_mr = 0; // the sum of the mass times the radius
                int sum_m = 0; // the sum of the masses
                for (int i = 0; i < bmp.getWidth(); i++) {
                    int gsr = abs(green(pixels[i])-red(pixels[i]));
                    int gsb = abs(green(pixels[i])-blue(pixels[i]));
                    int rsb = abs(red(pixels[i])-blue(pixels[i]));
                    if (gsr < range && gsb < range && rsb < range && green(pixels[i]) > thresh) {
                        pixels[i] = rgb(1, 1, 1); // set the pixel to almost 100% black

                        sum_m = sum_m + green(pixels[i]) + red(pixels[i]) + blue(pixels[i]);
                        sum_mr = sum_mr + (green(pixels[i]) + red(pixels[i]) + blue(pixels[i])) * i;
                    }
                }
                // only use the data if there were a few pixels identified, otherwise you might get a divide by 0 error
                if (sum_m > 5) {
                    COM = sum_mr / sum_m;
                    canvas.drawCircle(COM, startY, 5, paint1); // x position, y position, diameter, color
                } else {
                    COM = 0;
                }
                bmp.setPixels(pixels, 0, bmp.getWidth(), 0, startY, bmp.getWidth(), 1);
            }
            /*
            //int thresh = 0; // comparison value
            int gap = 3;
            int height = bmp.getHeight()/gap;
            int[][] pixels = new int[height][bmp.getWidth()]; // pixels[] is the RGBA data
            //int startY = 200; // which row in the bitmap to analyze to read

            for (int startY = 0; startY < height; startY++) {
                bmp.getPixels(pixels[startY], 0, bmp.getWidth(), 0, startY*gap, bmp.getWidth(), 1);
                // in the row, see if there is more green than red
                for (int i = 0; i < bmp.getWidth(); i++) {
                    //if (((green(pixels[i]) - red(pixels[i])) > thresh)&&((green(pixels[i]) - blue(pixels[i])) > thresh)) {
                     if ((green(pixels[startY][i])*3-(green(pixels[startY][i])+red(pixels[startY][i])+blue(pixels[startY][i]))) > thresh){
                        pixels[startY][i] = rgb(0, 255, 0); // over write the pixel with pure green
                    }
                }
                // update the row
                bmp.setPixels(pixels[startY], 0, bmp.getWidth(), 0, startY*gap, bmp.getWidth(), 1);
            }
            */
        }

        /*
        // draw a circle at some position
        int pos = 50;
        canvas.drawCircle(pos, 50, 5, paint1); // x position, y position, diameter, color

        // write the pos as text
        canvas.drawText("pos = " + pos, 10, 30, paint1);
*/        c.drawBitmap(bmp, 0, 0, null);
        mSurfaceHolder.unlockCanvasAndPost(c);

        // calculate the FPS to see how fast the code is running
        long nowtime = System.currentTimeMillis();
        long diff = nowtime - prevtime;
        mTextView.setText("FPS " + 1000 / diff);
        prevtime = nowtime;
    }
}