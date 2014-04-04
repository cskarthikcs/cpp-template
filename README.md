C++ template with potentially useful libraries pre-installed.

Quickstart:

Create account, project and instance.

Install GCE and setup instance:

    sudo apt-get install curl
    curl https://dl.google.com/dl/cloudsdk/release/install_google_cloud_sdk.bash | bash
    gcloud auth login
    getproject --project="PROJECT_NAME" --cache_flag_values

Login SSH, get source, compile and run:

    gcutil --service_version="v1" --project="PROJECT_NAME" ssh --zone="europe-west1-b" "INSTANCE_NAME"
    sudo apt-get update
    sudo apt-get install git
    git clone --recursive https://github.com/google-hash-code-paris-2014-tmo/cpp-template
    cd cpp-template
    ./configure
    make run

Header only implementation because this is a coding context, so writing faster is more important than compiling faster.

Based on: <https://github.com/cirosantilli/cpp-template>

All input data must be put under directory `input/`.
