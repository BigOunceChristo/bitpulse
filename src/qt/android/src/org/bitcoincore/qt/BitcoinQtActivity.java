package org.bitpulsecore.qt;

import android.os.Bundle;
import android.system.ErrnoException;
import android.system.Os;

import org.qtproject.qt5.android.bindings.QtActivity;

import java.io.File;

public class bitpulseQtActivity extends QtActivity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        final File bitpulseir = new File(getFilesDir().getAbsolutePath() + "/.bitpulse");
        if (!bitpulseir.exists()) {
            bitpulseir.mkdir();
        }

        super.onCreate(savedInstanceState);
    }
}
