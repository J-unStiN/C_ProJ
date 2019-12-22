package com.example.user.quiz;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;

public class MainActivity extends AppCompatActivity {

    private String level;
    private EditText editTextNickname;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        level = "Easy";
        editTextNickname = findViewById(R.id.editTextNickname);
    }

    public void onEnter(View view){
        String nickname = editTextNickname.getText().toString();
        if(nickname.length() == 0)
            return;

        Intent intent = new Intent(this, QuizActivity.class);
        intent.putExtra("nickname", nickname);
        intent.putExtra("level", level);
        startActivity(intent);
    }

    public void onRadioButton(View view){
        if(view.getId() == R.id.radioButtonEasy)
            level = "Easy";
        else
            level = "Hard";
    }
}
