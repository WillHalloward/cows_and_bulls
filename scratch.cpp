//Example on how to build a number with unique digits instead of filter out.
static ArrayList<String> getNonDuplicatedNumbers(int len, ArrayList<Integer> digits) {
    ArrayList<String> numbers = new ArrayList<String>();
    if (digits.size() >= len) {
        numbers.add(digits.stream().map(i -> Integer.toString(i)).collect(Collectors.joining("")));
        return numbers;
    } else {
        for (int x = 0; x < 10; x++) {
            if (digits.indexOf(x) < 0) {
                ArrayList<Integer> newDigits = (ArrayList<Integer>)digits.clone();
                newDigits.add(x);
                numbers.addAll(getNonDuplicatedNumbers(len, newDigits));
            }
        }
    }
    return numbers;
}
//Example on how to build a number with unique digits instead of filter out.
ArrayList<String> getNonDuplicatedNumbers(int len) {
    HashSet<Character> digits = new HashSet<Character>();
    ArrayList<String> numbers = new ArrayList<String>();
    for (int x = 0; x < 10; x++) {
        digits.add((char)(x + 48));
        numbers.add(Integer.toString(x));
    }
    int numLength = 1;
    int index = 1;
    int lastStart = 0;
    for (; numLength < len; numLength++) {
        lastStart = index;
        int startSize = numbers.size();
        for (; index < startSize; index++) {
            HashSet<Character> unusedDigits = (HashSet<Character>)digits.clone();
            String toCheck = numbers.get(index);
            for (int ch = 0; ch < toCheck.length(); ch++) {
                unusedDigits.remove(toCheck.charAt(ch));
            }
            for (char digit : unusedDigits) {
                numbers.add(numbers.get(index) + digit);
            }
        }
    }
    for (int x = numbers.size() - 1; x >= 0; x--) {
        String number = numbers.get(x);
        if (number.length() < len) {
            if (number.length() < len - 1 || number.indexOf('0') > -1) {
                numbers.remove(x);
            }
            else {
                numbers.set(x, "0" + number);
            }
        }
    }
    return numbers;
}