package net.anhero;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
import javax.microedition.khronos.egl.*;

import android.app.*;
import android.content.*;
import android.view.*;
import android.os.*;
import android.util.Log;
import android.graphics.*;
import android.text.method.*;
import android.text.*;
import android.media.*;
import android.hardware.*;
import android.content.*;

import java.lang.*; 

public class BaconBoxActivity extends Activity
{

	private static BaconBoxActivity activitySingleton;
    private static BaconBoxSurface surface;


	static {
        //System.loadLibrary("BaconBox");
        System.loadLibrary("BaconBoxApp");
		
	}

	@Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
		
        surface = new BaconBoxSurface(getApplication());
        setContentView(surface);
        
        activitySingleton = this;
	//	this.requestWindowFeature(Window.FEATURE_NO_TITLE);
	//this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN );
		
        			
    }

	@Override
	protected void onPause() {
        super.onPause();
    }
	
	@Override
	protected void onResume() {
        super.onResume();
    }

    public static native void nativeInit();

	public static native void onNativeTouch(int action, float x, 
                                            float y, float p);
    public static native void onNativeAccel(float x, float y, float z);
	public static native void onNativeKeyDown(int keycode);
    public static native void onNativeKeyUp(int keycode);
										




	public static void createGLContext() {
		surface.initEGL();
    }

	public static void flipBuffers() {
        surface.flipEGL();
    }

}; 

class BaconBoxMain implements Runnable {
    public void run() {
        BaconBoxActivity.nativeInit();

    }
}
class BaconBoxSurface extends SurfaceView implements SurfaceHolder.Callback, 
    View.OnKeyListener, View.OnTouchListener, SensorEventListener {
	
	private Thread BaconBoxThread; 

	private EGLContext  context;
    private EGLSurface  surface;
    private EGLDisplay  display;

    private static SensorManager sensorManager;

	public BaconBoxSurface(Context context) {
        super(context);
		getHolder().addCallback(this);
		setFocusable(true);
        setFocusableInTouchMode(true);
        requestFocus();
        setOnKeyListener(this); 
        setOnTouchListener(this);   

        sensorManager = (SensorManager)context.getSystemService("sensor");  
    }

	public void surfaceCreated(SurfaceHolder holder) {
        enableSensor(Sensor.TYPE_ACCELEROMETER, true);
    }

	public void surfaceChanged(SurfaceHolder holder,
                               int format, int width, int height) {

									if(baconBoxThread == null){
										baconBoxThread = new Thread(new BaconBoxMain(), "BaconBoxThread");
										baconBoxThread.start();
									}
							   }

    public void onDraw(Canvas canvas) {}
	public void surfaceDestroyed(SurfaceHolder holder) {}


	
	 public void initEGL(){
		EGL10 egl = (EGL10)EGLContext.getEGL();
		EGLDisplay dpy = egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
		int[] version = new int[2];
		egl.eglInitialize(dpy, version);
		int EGL_OPENGL_ES_BIT = 1;

		int[] configSpec = {
                EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT,
                EGL10.EGL_NONE
            };
		EGLConfig[] configs = new EGLConfig[1];
        int[] num_config = new int[1];

		if (!egl.eglChooseConfig(dpy, configSpec, configs, 1, num_config) || num_config[0] == 0) {
                Log.e("BaconBox", "No EGL config available");
            }
		EGLConfig config = configs[0];

		EGLContext ctx = egl.eglCreateContext(dpy, config, EGL10.EGL_NO_CONTEXT, null);
            if (ctx == EGL10.EGL_NO_CONTEXT) {
                Log.e("BaconBox", "Couldn't create context");
            }

			EGLSurface tempSurface = egl.eglCreateWindowSurface(dpy, config, this, null);
            if (surface == EGL10.EGL_NO_SURFACE) {
                Log.e("BaconBox", "Couldn't create surface");
            }

			if (!egl.eglMakeCurrent(dpy, tempSurface, tempSurface, ctx)) {
                Log.e("BaconBox", "Couldn't make context current");
            }

			context = ctx;
            display = dpy;
            surface = tempSurface;
	 }

	public void flipEGL() {
		try {
	EGL10 egl = (EGL10)EGLContext.getEGL();
	

	egl.eglWaitNative(EGL10.EGL_NATIVE_RENDERABLE, null);
	egl.eglWaitGL();

    egl.eglSwapBuffers(display, surface);
		} catch(Exception e) {
            Log.v("SDL", "flipEGL(): " + e);
            for (StackTraceElement s : e.getStackTrace()) {
                Log.v("SDL", s.toString());
            }
        }

	}
	public boolean onKey(View  v, int keyCode, KeyEvent event) {

        if (event.getAction() == KeyEvent.ACTION_DOWN) {
            BaconBoxActivity.onNativeKeyDown(keyCode);
            return true;
        }
        else if (event.getAction() == KeyEvent.ACTION_UP) {
            BaconBoxActivity.onNativeKeyUp(keyCode);
            return true;
        }
        
        return false;
    }

	public boolean onTouch(View v, MotionEvent event) {
        int action = event.getAction();
        float x = event.getX();
        float y = event.getY();
        float p = event.getPressure();

        BaconBoxActivity.onNativeTouch(action, x, y, p);
        return true;
    }

	public void enableSensor(int sensortype, boolean enabled) {
        if (enabled) {
            sensorManager.registerListener(this, 
                            sensorManager.getDefaultSensor(sensortype), 
                            SensorManager.SENSOR_DELAY_GAME, null);
        } else {
            sensorManager.unregisterListener(this, 
                            sensorManager.getDefaultSensor(sensortype));
        }
    }

	public void onAccuracyChanged(Sensor sensor, int accuracy) {
    }

	public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            BaconBoxActivity.onNativeAccel(event.values[0],
                                      event.values[1],
                                      event.values[2]);
        }
    }
};


