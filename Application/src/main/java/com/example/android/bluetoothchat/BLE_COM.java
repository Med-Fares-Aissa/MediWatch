/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


package com.example.android.bluetoothchat;


import android.Manifest;
import android.annotation.SuppressLint;
import android.content.pm.PackageManager;
import android.location.Address;
import android.location.Geocoder;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.Handler;

import android.view.Menu;
import android.view.MenuItem;

import android.widget.TextView;

import androidx.annotation.NonNull;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import com.example.android.common.activities.SampleActivityBase;
import com.example.android.common.logger.Log;

import com.example.android.common.logger.LogWrapper;
import com.example.android.common.logger.MessageOnlyLogFilter;

import com.google.android.gms.tasks.OnFailureListener;
import com.google.android.gms.tasks.OnSuccessListener;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.DocumentSnapshot;
import com.google.firebase.firestore.FirebaseFirestore;

import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;


/**
 * A simple launcher activity containing a summary sample description, sample log and a custom
 * {@link Fragment} which can display a view.
 * <p>
 * For devices with displays with a width of 720dp or greater, the sample log is always visible,
 * on other devices it's visibility is controlled by an item on the Action Bar.
 */
public class BLE_COM extends SampleActivityBase implements LocationListener {
    int a = 0 ;
    String Adreesse ;
    TextView textView_localisation ;
    Date currentTime ;
    LocationManager locationmanager ;
    boolean logiin = true ;
    public static final String TAG = "MainActivity";
/////////////////////////////////////////////
FirebaseAuth fAuth  = FirebaseAuth.getInstance();
    String idUser = fAuth.getCurrentUser().getUid();
    FirebaseFirestore db = FirebaseFirestore.getInstance();
    DocumentReference noteRef = db.collection("users").document(idUser);
    //get data
    String LongitudeSiteWebb ;
    boolean Statuee  ;
    String LatitudeSiteWebb ;
    String longitude_real_time ;
    String latitude_real_time ;
    float LongitudeSiteWeb;
    float LatitudeSiteWeb ;
    String location ;
    String locationACC ;
    double comparaison ;
    boolean retour ;
    String comparaisonString ;
    ////////////////////////////////////////
    // Whether the Log Fragment is currently shown
    private boolean mLogShown;

    Handler handler;
    boolean OldRetour;

    @Override
    protected void onCreate(Bundle savedInstanceState) {


            super.onCreate(savedInstanceState);
            setContentView(R.layout.activity_b_l_e__c_o_m);
            if (savedInstanceState == null) {
                FragmentTransaction transaction = getSupportFragmentManager().beginTransaction();
                BluetoothChatFragment fragment = new BluetoothChatFragment();
                transaction.replace(R.id.sample_content_fragment, fragment);
                transaction.commit();
            }

        getData () ;
        //BASE DE DONEEEEEE
        // Create a new user with a first, middle, and last name
        Map<String, Object> user = new HashMap<>();
        user.put("latitude_real_time", ".");
        user.put("longitude_real_time", ".");
        user.put("location_real_time", ".");
        user.put("Statue", retour);
        noteRef.update(user);
        textView_localisation = findViewById(R.id.textView4);
        //Naamlo permission lel GPS
        if (ContextCompat.checkSelfPermission(BLE_COM.this , Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED){
            ActivityCompat.requestPermissions(BLE_COM.this ,new String[]{
                    Manifest.permission.ACCESS_FINE_LOCATION
            }, 100);
        }
        getLoccation();
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {

        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        return super.onOptionsItemSelected(item);
    }

    /**
     * Create a chain of targets that will receive log data
     */
    @Override
    public void initializeLogging() {
        // Wraps Android's native log framework.
        LogWrapper logWrapper = new LogWrapper();
        // Using Log, front-end to the logging chain, emulates android.util.log method signatures.
        Log.setLogNode(logWrapper);

        // Filter strips out everything except the message text.
        MessageOnlyLogFilter msgFilter = new MessageOnlyLogFilter();
        logWrapper.setNext(msgFilter);

        // On screen logging via a fragment with a TextView.
        /*LogFragment logFragment = (LogFragment) getSupportFragmentManager()
                .findFragmentById(R.id.log_fragment);*/
        //msgFilter.setNext(logFragment.getLogView());

        Log.i(TAG, "Ready");
    }


    void getData (){
//
//        DocumentReference noteRef = db.document("users/" +idUser);
        ////////////////////////////// recevoir DATA /////////////

        noteRef.get()
                .addOnSuccessListener(new OnSuccessListener<DocumentSnapshot>() {
                    @Override
                    public void onSuccess(DocumentSnapshot documentSnapshot) {
                        if (documentSnapshot.exists()) {
                            longitude_real_time = documentSnapshot.getString("longitude_real_time");
                            latitude_real_time = documentSnapshot.getString("latitude_real_time");
                            LongitudeSiteWebb = documentSnapshot.getString("longitude") ;
                            LatitudeSiteWebb = documentSnapshot.getString("Latitude") ;
                            OldRetour = documentSnapshot.getBoolean("Statue"); ;
//                            textView_localisation.setText(LongitudeSiteWebb);
                        }
                        else {
                        }
                    }
                })
                .addOnFailureListener(new OnFailureListener() {
                    @Override
                    public void onFailure(@NonNull Exception e) {
                    }
                });

    }
    Boolean com(float longi , float lati  ){
        //TRAITEMENT

        LongitudeSiteWeb = Float.parseFloat(LongitudeSiteWebb);
        LatitudeSiteWeb = Float.parseFloat(LatitudeSiteWebb);
        float x = (float) ((longi - LongitudeSiteWeb ) * Math.cos((lati+LatitudeSiteWeb)/2));
        float y = (float) (lati-LatitudeSiteWeb);
        double z = Math.sqrt((x*x)+(y*y)) ;
        comparaison = z * 1.852 * 60 ;

        // Add a new document with a generated ID
        comparaisonString = String.valueOf(comparaison);
//        textView_localisation.setText(comparaisonString);

        if ( comparaison > 0.5){
            retour = true;
            // addNotification() ;
        }
        else{
            retour = false ;
        }
        //FIN traitement
        //update
        return retour ;
    }
    @SuppressLint("MissingPermission")
    private void getLoccation(){
        try {
            locationmanager = (LocationManager) getApplicationContext().getSystemService(LOCATION_SERVICE);
            locationmanager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 5000 , 5 , BLE_COM.this);

        }catch(Exception e){
            e.printStackTrace();
        }

    }

    @Override
    public void onLocationChanged(@NonNull Location location) {
//        Toast.makeText(this , ""+location.getLatitude()+","+location.getLongitude(), Toast.LENGTH_SHORT).show();
        try {
            Geocoder geocoder = new Geocoder(BLE_COM.this , Locale.getDefault());

            List<Address> addresses = geocoder.getFromLocation(location.getLatitude(),location.getLongitude(),1);
            String address = addresses.get(0).getAddressLine(0);
            //Toast.makeText(this , ""+location.getLatitude()+","+location.getLongitude(), Toast.LENGTH_SHORT).show();

//            textView_localisation.setText(address+" "+location.getLatitude()+","+location.getLongitude() );
            getData () ;

            com((float) location.getLongitude() , (float) location.getLatitude() ) ;


      if (retour != OldRetour ) {
          //BASE DE DONEEEEEE
          // Create a new user with a first, middle, and last name
          Map<String, Object> user = new HashMap<>();
          user.put("latitude_real_time", Double.toString(location.getLatitude()));
          user.put("longitude_real_time", Double.toString(location.getLongitude()));
          user.put("location_real_time", address);
          user.put("Statue", retour);
          noteRef.update(user);
      }
      else {
          textView_localisation.setText(" ");
      }

        }catch(Exception e){
            e.printStackTrace();
        }
    }
    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {

    }

    @Override
    public void onProviderEnabled(@NonNull String provider) {

    }

    @Override
    public void onProviderDisabled(@NonNull String provider) {

    }


//    void SendData(){
//
//        // Create a new user with a first, middle, and last name
//        Map<String, Object> user = new HashMap<>();
//        user.put("Statue",retour);
//        noteRef.update(user);
//
//    }

}
